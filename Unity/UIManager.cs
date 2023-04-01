using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

/*
    ### 각 버튼과 그에 해당하는 패널은 이름이 같아야 함 앞에 btn pnl은 붙여주고 ###
    정렬 방식

    메인메뉴

    UI(캔버스) ( 태그 CANVAS )
    {
        - 메인화면 버튼 모음집
            - 메인화면 버튼들

        - 판넬 모음집 ( 이름 pnlUI )( 태그 UI )
            - 메인메뉴 판넬
                - 종료 버튼 ( 태그 BUTTON )
                - 서브메뉴 판넬
                - 서브메뉴 버튼모음집 ( 태그 BUTTON )
                    - 서브메뉴 버튼들
    }
*/

public class UIManager : MonoBehaviour
{
    // 클릭된 버튼을 담는다
    private Transform btn;
    // 클릭된 버튼의 이름을 담는다
    private string btnName;
    // 버튼으로 접근할 대상을 담는다
    private Transform target;

    // 메인 메뉴 버튼용 함수
    public void OnMainMenuSelect()
    {
        // 현재 클릭된 이벤트시스템 오브젝트를 btn객체에 담는다
        btn = EventSystem.current.currentSelectedGameObject.transform;
        // 이름도 담아준다
        btnName = EventSystem.current.currentSelectedGameObject.name;
        // 이름에서 앞 3글자를 pnl로 바꾼다 ( btn -> pnl )
        btnName = "pnl" + btnName.Substring(3);

        // 회색 바탕을 먼저 활성화 시켜준다 (제일 부모이기도 하고 카메라 이동도 막아주는 역할)
        GameObject.FindWithTag("CANVAS").transform.Find("pnlUI").gameObject.SetActive(true);
        // 이름에 맞는 게임오브젝트를 메인메뉴들중에 찾고 활성화
        GameObject.FindWithTag("UI").transform.Find(btnName).gameObject.SetActive(true);
    }

    // 서브 메뉴 버튼용 함수
    public void OnSubMenuSelect()
    {
        // 현재 클릭된 이벤트시스템 오브젝트를 btn객체에 담는다
        btn = EventSystem.current.currentSelectedGameObject.transform;
        // 이름도 담아준다
        btnName = EventSystem.current.currentSelectedGameObject.name;
        // 이름에서 앞 3글자를 pnl로 바꾼다 ( btn -> pnl )
        btnName = "pnl" + btnName.Substring(3);

        // 버튼 모음집의 부모에서 이름이 맞는 게임오브젝트를 찾아서 담아준다
        target = btn.parent.parent.Find(btnName);

        // 키고 싶은 창의 형제들을 모두 비활성화 시켜준다 안하면 하이아키상 제일 밑에있는 창만 보인다
        foreach (Transform t in target.parent)
        {
            // 버튼은 비활성화 시키면 안되기에 예외시킨다
            if (t.gameObject.tag != "BUTTON")
                t.gameObject.SetActive(false);
        }

        // 형제들을 다 비활성화 시켰기에 마지막에 본인을 활성화 시킨다
        target.gameObject.SetActive(true);
    }

    // 닫기 버튼용 함수
    public void OnExitBtnSelect()
    {
        // 닫기 버튼을 따로 담아준다
        Transform exitBtn;
        exitBtn = EventSystem.current.currentSelectedGameObject.transform;
        
        // 해당 버튼의 부모를 비활성화 하고 (하이아키로 보면 킨 창)
        exitBtn.parent.gameObject.SetActive(false);
        // 회색 바탕도 같이 비활성화한다
        GameObject.FindWithTag("CANVAS").transform.Find("pnlUI").gameObject.SetActive(false);
    }
}
