using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BattleEndText : MonoBehaviour
{
    public GameObject success;
    public GameObject fail;
    public GameObject zero;
    [HideInInspector]
    public ArmyManager army;

    // Start is called before the first frame update
    void Start()
    {
        army = GameObject.FindObjectOfType<ArmyManager>();
    }

    // Update is called once per frame
    void Update()
    {
        Invoke("ShowText", 2);
    }

    void ShowText()
    {
        if (!GameObject.FindGameObjectWithTag("BUILDING"))
            success.SetActive(true);

        if (!GameObject.FindGameObjectWithTag("ATTACKUNIT")
            && army.units.Find(u => u.name.Contains("soldier")).num == 0 && army.units.Find(u => u.name.Contains("archer")).num == 0
            && army.units.Find(u => u.name.Contains("knight")).num == 0 && army.units.Find(u => u.name.Contains("horsearcher")).num == 0
            && army.units.Find(u => u.name.Contains("cleric")).num == 0 && army.units.Find(u => u.name.Contains("wizard")).num == 0
            && army.units.Find(u => u.name.Contains("catapult")).num == 0)
            fail.SetActive(true);
    }
}

