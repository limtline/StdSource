using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public static class PlacementHelpers
{
    // 레이를 어따 쏠꺼냐
    public static bool RaycastFromMouse(out RaycastHit hit, LayerMask layer)
    {
        // 일단 메인카메라의 마우스 포지션 좌표에 
        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
        // 레이저를 무한대로 쏘고
        if (Physics.Raycast(ray, out hit, Mathf.Infinity, layer))
        {
            return true;    
        }
        return false;
    }

    public static void ToggleRenderers(GameObject obj, bool toggle)
    {
        if (!obj)   // 게임오브젝트가 없다면.
            return; // 리턴

        // 게임 오브젝트의 자식 렌더러 컴포넌트를 배열로 담는다
        Renderer[] renderers = obj.GetComponentsInChildren<Renderer>();

        // 렌더러의 길이가 0보다 크면,
        if (renderers.Length > 0)
        {
            foreach (Renderer r in renderers)
                // 렌더러를 bool 값으로 받는데, (enabled 가 약간 Setactive랑 비슷함)
                r.enabled = toggle; // toggle이 false면 비활성, true면 활성화임
        }
    }

    public static Rect MakeRectOfCollider(Collider col)
    {
        // 콜라이더의 렉탱글 위치를 잡아 만든다. 정 4면으로 만들어질 수 있게
        Rect rec = new Rect(col.bounds.center.x - col.bounds.extents.x,
            col.bounds.center.z - col.bounds.extents.z,
            col.bounds.size.x, col.bounds.size.z);
        return rec;
    }

    public static bool IsButtonPressed(GraphicRaycaster raycaster)
    {
        // 현재 클릭된 UI가 없다면,
        if (!EventSystem.current)
            return true;    // true를 리턴

        // 클릭과 터치 상태에 따른 이벤트를 초기화해줌
        PointerEventData eventData = new PointerEventData(EventSystem.current);
        // 리스트에 ui를 쏜 레이를 담음 ??? 맞나 ???
        List<RaycastResult> results = new List<RaycastResult>();
        // 클릭과 터치 상태 위치를 마우스 위치로
        eventData.position = Input.mousePosition;
        // UI에 레이를 쏨
        raycaster.Raycast(eventData, results);
        return results.Count != 0;
    }
}
