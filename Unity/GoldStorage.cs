using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GoldStorage : MonoBehaviour
{
    GameObject btnI;
    Animator anim;

    public int myGold;
    public int maxGold = 900;

    private void Awake()
    {
        btnI = transform.GetChild(1).gameObject;
        anim = GetComponent<Animator>();
    }

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        if (myGold >= maxGold)
        {
            myGold = Mathf.Clamp(myGold, 0, maxGold);
        }
    }

    public void BtnClick()
    {
        anim.SetTrigger("BtnClick");
    }
    
    void OnCollisionEnter(Collision col)
    {
        if(col.gameObject.tag == "Arrow")
            Destroy(gameObject);
    }
}
