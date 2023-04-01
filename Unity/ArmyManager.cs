using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public enum eUnit
{
    SOLDIER = 0,
    ARCHER,
    KNIGHT,
    HORSEARCHER,
    CLERIC,
    WIZARD,
    CATAPULT
}

public class UnitI
{
    private string Name;
    private int Level;
    private int Num;

    public string name
    {
        get { return Name; }
        set { Name = value; }
    }

    public int level
    {
        get { return Level; }
        set { Level = value; }
    }
    public int num
    {
        get { return Num; }
        set { Num = value; }
    }
}

public class ArmyManager : MonoBehaviour
{
    public List<UnitI> units = new List<UnitI>();

    [HideInInspector]
    public string phpURL = "http://unitycoc.dothome.co.kr/armyLoading.php";
    [HideInInspector]
    public string jsonURL = "http://unitycoc.dothome.co.kr/armyLoading.json";
    [HideInInspector]
    public string phpSendURL = "http://unitycoc.dothome.co.kr/saveArmy.php";

    public eUnit EUnit = eUnit.SOLDIER;
    private string name;
    public int level;
    public int num;

#if UNITY_EDITOR
    void Update()
    {
        switch (EUnit)
        {
            case eUnit.SOLDIER:
                name  = "soldier";
                level = units.Find(u => u.name.Contains(name)).level;
                num   = units.Find(u => u.name.Contains(name)).num;
                break;
            
            case eUnit.ARCHER:
                name  = "archer";
                level = units.Find(u => u.name.Contains(name)).level;
                num   = units.Find(u => u.name.Contains(name)).num;
                break;
            
            case eUnit.KNIGHT:
                name  = "knight";
                level = units.Find(u => u.name.Contains(name)).level;
                num   = units.Find(u => u.name.Contains(name)).num;
                break;
            
            case eUnit.HORSEARCHER:
                name  = "horsearcher";
                level = units.Find(u => u.name.Contains(name)).level;
                num   = units.Find(u => u.name.Contains(name)).num;
                break;
            
            case eUnit.CLERIC:
                name  = "cleric";
                level = units.Find(u => u.name.Contains(name)).level;
                num   = units.Find(u => u.name.Contains(name)).num;
                break;
            
            case eUnit.WIZARD:
                name  = "wizard";
                level = units.Find(u => u.name.Contains(name)).level;
                num   = units.Find(u => u.name.Contains(name)).num;
                break;
            
            case eUnit.CATAPULT:
                name  = "catapult";
                level = units.Find(u => u.name.Contains(name)).level;
                num   = units.Find(u => u.name.Contains(name)).num;
                break;
        }
    }
#endif
}
