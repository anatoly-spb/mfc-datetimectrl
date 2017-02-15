#include "stdafx.h"

#include "RDateTimeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CRDateTimeCtrl, CDateTimeCtrl)
  ON_NOTIFY_REFLECT_EX(DTN_CLOSEUP, &CRDateTimeCtrl::OnDtnCloseup)
  ON_NOTIFY_REFLECT_EX(DTN_DATETIMECHANGE, &CRDateTimeCtrl::OnDtnDatetimechange)
  ON_NOTIFY_REFLECT_EX(DTN_DROPDOWN, &CRDateTimeCtrl::OnDtnDropdown)
  ON_NOTIFY_REFLECT_EX(DTN_FORMAT, &CRDateTimeCtrl::OnDtnFormat)
  ON_NOTIFY_REFLECT_EX(DTN_FORMATQUERY, &CRDateTimeCtrl::OnDtnFormatquery)
  ON_NOTIFY_REFLECT_EX(DTN_USERSTRING, &CRDateTimeCtrl::OnDtnUserstring)
  ON_NOTIFY_REFLECT_EX(DTN_WMKEYDOWN, &CRDateTimeCtrl::OnDtnWmkeydown)
  ON_WM_CHAR()
  ON_WM_KEYDOWN()
  ON_WM_KEYUP()
  ON_WM_KILLFOCUS()
  ON_WM_SETFOCUS()
  ON_WM_LBUTTONDOWN()
  ON_WM_MBUTTONDOWN()
  ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

CRDateTimeCtrl::CRDateTimeCtrl() : field_(CHECK), blocked_(false), change_count_(0), wm_char_blocked_(false)
{
}


CRDateTimeCtrl::~CRDateTimeCtrl()
{
}


BOOL CRDateTimeCtrl::OnDtnCloseup(NMHDR *pNMHDR, LRESULT *pResult)
{
  // TODO: Add your control notification handler code here
  TRACE(_T("OnDtnCloseup\n"));
  *pResult = 0;
  // If you use ON_NOTIFY_REFLECT_EX() in your message map, your message 
  // handler may or may not allow the parent window to handle the message.
  // If the handler returns FALSE, the message will be handled by the parent as well, 
  // while a call that returns TRUE does not allow the parent to handle it.
  // Note that the reflected message is handled before the notification message.
  return FALSE;
}


BOOL CRDateTimeCtrl::OnDtnDatetimechange(NMHDR *pNMHDR, LRESULT *pResult)
{
  TRACE(_T("OnDtnDatetimechange\n"));
  LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
  if (blocked_) {
    last_ = *pDTChange;
    // нотификацию получает родитель
    return FALSE;
  }
  if (last_) {
    if (pDTChange->dwFlags == GDT_VALID) {
      TRACE(_T("OnDtnDatetimechange: %s: %d-%d-%d %d:%d:%d\n"), _T("VALID"), pDTChange->st.wYear, pDTChange->st.wMonth, pDTChange->st.wDay, pDTChange->st.wHour, pDTChange->st.wMinute, pDTChange->st.wSecond);
    } else 
    if (pDTChange->dwFlags == GDT_NONE) {
      TRACE(_T("OnDtnDatetimechange: %s\n"), _T("NOT VALID"));
    }
    // флаг не изменилс€
    if (pDTChange->dwFlags == last_->dwFlags && pDTChange->dwFlags == GDT_VALID) {
      // провер€ем модификацию года
      if (pDTChange->st.wYear != last_->st.wYear) {
      }
      // провер€ем модификацию мес€ца
      if (pDTChange->st.wMonth != last_->st.wMonth) {
      }
      // провер€ем модификацию дн€
      if (pDTChange->st.wDay != last_->st.wDay) {
        // 
        TRACE(_T("OnDtnDatetimechange: old: %d, new: %d\n"), last_->st.wDay, pDTChange->st.wDay);
      }
    }
  }
  // инициализаци€
  last_ = *pDTChange;

  *pResult = 0;
  return FALSE;
}


BOOL CRDateTimeCtrl::OnDtnDropdown(NMHDR *pNMHDR, LRESULT *pResult)
{
  TRACE(_T("OnDtnDropdown\n"));
  *pResult = 0;
  // allow parent to get notification
  return FALSE;
}


BOOL CRDateTimeCtrl::OnDtnFormat(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMDATETIMEFORMAT pDTFormat = reinterpret_cast<LPNMDATETIMEFORMAT>(pNMHDR);
  TRACE(_T("OnDtnFormat\n"));
  *pResult = 0;
  // allow parent to get notification
  return FALSE;
}


BOOL CRDateTimeCtrl::OnDtnFormatquery(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMDATETIMEFORMATQUERY pDTFmtQuery = reinterpret_cast<LPNMDATETIMEFORMATQUERY>(pNMHDR);
  TRACE(_T("OnDtnFormatquery\n"));
  *pResult = 0;
  // allow parent to get notification
  return FALSE;
}


BOOL CRDateTimeCtrl::OnDtnUserstring(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMDATETIMESTRING pDTString = reinterpret_cast<LPNMDATETIMESTRING>(pNMHDR);
  TRACE(_T("OnDtnUserstring\n"));
  *pResult = 0;
  // allow parent to get notification
  return FALSE;
}


BOOL CRDateTimeCtrl::OnDtnWmkeydown(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMDATETIMEWMKEYDOWN pDTKeyDown = reinterpret_cast<LPNMDATETIMEWMKEYDOWN>(pNMHDR);
  TRACE(_T("OnDtnWmkeydown\n"));
  *pResult = 0;
  // allow parent to get notification
  return FALSE;
}


void CRDateTimeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  TRACE(_T("OnKeyDown(%d, %d, %d)\n"), nChar, nRepCnt, nFlags);
  switch (nChar) {
  case '0': case '1':case '2': case '3':case '4':case '5':case '6':case '7':case '8':case '9':
    wm_char_blocked_ = true;
    break;
  case VK_DELETE:
    wm_char_blocked_ = true;
    SetTime();
    break;
  }
  CDateTimeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CRDateTimeCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  CString old_text;
  GetWindowText(old_text);

  CString ch(static_cast<wchar_t>(nChar));
  text_ += ch;

  TRACE(_T("OnChar(%d (%s), %d, %d)\n"), nChar, ch, nRepCnt, nFlags);

  if (!wm_char_blocked_) {
    CDateTimeCtrl::OnChar(nChar, nRepCnt, nFlags);
  }
  CString new_text;
  GetWindowText(new_text);

  TRACE(_T("OnChar: old: %s, new: %s\n"), old_text, new_text);
}



void CRDateTimeCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  TRACE(_T("OnKeyUp(%d, %d, %d)\n"), nChar, nRepCnt, nFlags);
  wm_char_blocked_ = false;
  CDateTimeCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CRDateTimeCtrl::OnKillFocus(CWnd* pNewWnd)
{
  CDateTimeCtrl::OnKillFocus(pNewWnd);

  TRACE(_T("OnKillFocus\n"));
}


void CRDateTimeCtrl::OnSetFocus(CWnd* pOldWnd)
{
  CDateTimeCtrl::OnSetFocus(pOldWnd);

  TRACE(_T("OnSetFocus\n"));
}


void CRDateTimeCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
  TRACE(_T("OnLButtonDown: %d (%d, %d)\n"), nFlags, point.x, point.y);

  CDateTimeCtrl::OnLButtonDown(nFlags, point);
}


void CRDateTimeCtrl::OnMButtonDown(UINT nFlags, CPoint point)
{
  TRACE(_T("OnMButtonDown: %d (%d, %d)\n"), nFlags, point.x, point.y);

  CDateTimeCtrl::OnMButtonDown(nFlags, point);
}


void CRDateTimeCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
  TRACE(_T("OnRButtonDown: %d (%d, %d)\n"), nFlags, point.x, point.y);

  CDateTimeCtrl::OnRButtonDown(nFlags, point);
}
