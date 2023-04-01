using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UITest : MonoBehaviour
{

    public Vector3 world;
    public Vector3 local;
    public Vector3 anchor;
    public Vector3 scale;
    public Vector3 localscale;
    public Vector2 sizeDelta;
    private RectTransform rect;
    GameObject test1;


    // Start is called before the first frame update
    void Start()
    {
        rect = transform.GetComponent<RectTransform>();
    }

    // Update is called once per frame
    void Update()
    {
        world = transform.position;
        local = transform.localPosition;
        anchor = rect.anchoredPosition;
        scale = transform.lossyScale;
        localscale = transform.localScale;
        sizeDelta = rect.sizeDelta;
    }
}
