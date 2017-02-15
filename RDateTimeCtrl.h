#pragma once

#include "afxdtctl.h"

/*
  —огласно документации по DateTime https://msdn.microsoft.com/library/windows/desktop/bb761726 элемент управлени€
  распознает следующие управл€ющие воздействи€:
  
  Arrow Keys 

  Ёлемент управлени€ принимает клавиши стрелок дл€ навигации по пол€м день, мес€ц, год и изменени€ значени€.

  The control accepts arrow keys to navigate the fields in the control and change values. 
  The user can press the or keys to move through the control If the user attempts to move past 
  the last field in a given direction, the keyboard focus "wraps around" to the field on the 
  opposite side of the control. The and keys change values in the current field incrementally.

  End and Home	

  The control accepts the VK_END and VK_HOME virtual keys to change the value within the current 
  field to its upper and lower limits, respectively.
    дл€ числа - первый и последний день мес€ца
    дл€ мес€ца - первый и последний мес€ц года
    дл€ года - 1601 до 9999

  Function Keys	
  
  The key activates edit mode. The key causes the control to display a drop-down month calendar 
  control (pressing does this as well).

  Numbers	

  The control accepts numeric input in two-character segments. If the value entered by the user 
  is invalid (like setting the month to 14), the control rejects it and resets the display to the previous value.

  Plus and Minus	

  The control accepts the VK_ADD and VK_SUBTRACT virtual keys from the numeric keypad to increment 
  and decrement the value in the current field.

  Ќовое поведение:
  
  элемент управление имеет два состо€ние VALID и NONE
  
  NONE 
  
  ¬ этом состо€нии показываетс€ только чекбокс. ѕри клике на поле ввода активируетс€ режим ожидани€ ввода

  при клике на поле ввода
*/
#include <boost/optional.hpp>

class CRDateTimeCtrl : public CDateTimeCtrl
{
  bool blocked_;
  boost::optional<NMDATETIMECHANGE> last_;
  /// перечисление полей
  enum FieldEnum {
    CHECK = 0,
    DAY,
    MONTH,
    YEAR,
    COUNT
  } field_;
  /// 
  CString text_;
  CString last_text_;
  int change_count_;
  bool wm_char_blocked_;
public:
  CRDateTimeCtrl();
  ~CRDateTimeCtrl();
  DECLARE_MESSAGE_MAP()
  afx_msg BOOL OnDtnCloseup(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg BOOL OnDtnDatetimechange(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg BOOL OnDtnDropdown(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg BOOL OnDtnFormat(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg BOOL OnDtnFormatquery(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg BOOL OnDtnUserstring(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg BOOL OnDtnWmkeydown(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnKillFocus(CWnd* pNewWnd);
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

