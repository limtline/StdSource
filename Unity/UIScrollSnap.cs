using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

[System.Serializable]
public class Padding
{
    public int x;
    public int y;
}

public class UIScrollSnap : MonoBehaviour
{
    public GameObject content;
    public Text numText;
    public Padding padding;
    public int spacing;
    private Vector2 posXY = Vector2.zero;

    //[HideInInspector]
    public Image[] images;
    public Image imageBack;
    public Image imageDeco;

    private Vector2 contentSize;
    private Vector2 imageSize;
    
    public Vector2 prePos;
    public Vector2 nowPos;
    public float dir;
    public int imageNum = 1;
    public bool clicked = false;

    void Awake()
    {
        images = content.GetComponentsInChildren<Image>();
        imageSize = images[1].GetComponent<RectTransform>().sizeDelta;

        contentSize = content.GetComponent<RectTransform>().sizeDelta;
        prePos = content.GetComponent<RectTransform>().anchoredPosition;
    }

    // Start is called before the first frame update
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        SetPosition();

        nowPos = content.GetComponent<RectTransform>().anchoredPosition;

        OnContentMove();

        if (clicked)
        {
            SnapMove();
        }

        numText.text = imageNum + " / 10";

        Mathf.Clamp(content.GetComponent<RectTransform>().anchoredPosition.x, -74.7f, 419.3f);

        if (imageBack == null)
            imageDeco.sprite = images[imageNum].sprite;
        else
            imageBack.sprite = images[imageNum].sprite;
    }

    void SetPosition()
    {
        for (int i = 1; i < images.Length; i++)
        {
            if (i == 1)
            {
                posXY.x = 0 + imageSize.x / 2 + padding.x;
                posXY.y = 0 - (imageSize.y / 2) - padding.y;
            }
            else
            {
                posXY.x += imageSize.x + spacing;                 
                posXY.y = 0 - (imageSize.y / 2) - padding.y;
            }
            images[i].GetComponent<RectTransform>().anchoredPosition = posXY;
        }
    }

    void OnContentMove()
    {
#if UNITY_EDITOR
        if (Input.GetMouseButton(0))
        {
            clicked = false;
            nowPos = content.GetComponent<RectTransform>().anchoredPosition;

            if (prePos.x > nowPos.x)
            {
                dir = -1;
                if (prePos.x - (imageSize.x + spacing) >= nowPos.x)
                {
                    prePos.x -= (imageSize.x + spacing);
                    imageNum++;
                }
            }
            else
            {
                dir = +1;
                if (prePos.x + (imageSize.x + spacing) <= nowPos.x)
                {
                    prePos.x += (imageSize.x + spacing);
                    imageNum--;
                }
            }
        }
        if (Input.GetMouseButtonUp(0))
        {
            clicked = true;
        }
#endif

#if UNITY_ANDROID
        if (Input.touchCount > 0)
        {
            Touch touch = Input.GetTouch(0);
            if (touch.phase == TouchPhase.Moved)
            {
                clicked = false;
                nowPos = content.GetComponent<RectTransform>().anchoredPosition;

                if (prePos.x > nowPos.x)
                {
                    dir = -1;
                    if (prePos.x - (imageSize.x + spacing) >= nowPos.x)
                    {
                        prePos.x -= (imageSize.x + spacing);
                        imageNum++;
                    }
                }
                else
                {
                    dir = +1;
                    if (prePos.x + (imageSize.x + spacing) <= nowPos.x)
                    {
                        prePos.x += (imageSize.x + spacing);
                        imageNum--;
                    }
                }
            }
            if (touch.phase == TouchPhase.Ended)
            {
                clicked = true;
            }
        }
#endif
    }

    void SnapMove()
    {
        Vector2 movePos = content.GetComponent<RectTransform>().anchoredPosition;
        movePos.x = Mathf.Lerp(movePos.x, prePos.x, Time.deltaTime * 3);

        content.GetComponent<RectTransform>().anchoredPosition = movePos;

        if (Mathf.Abs(prePos.x - movePos.x) <= 1f)
            clicked = false;
    }
}
