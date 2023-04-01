using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BuildingI
{
    private string Name;
    private int X;
    private int Z;

    public string name
    {
        get { return Name; }
        set { Name = value; }
    }
    public int x
    {
        get { return X; }
        set { X = value; }
    }
    public int z
    {
        get { return Z; }
        set { Z = value; }
    }
    public BuildingI()
    {

    }
    public BuildingI(string name, int x, int z)
    {
        this.name = name;
        this.x = x;
        this.z = z;
    }
}

public class TownManager : MonoBehaviour
{
    public List<BuildingI> buildings = new List<BuildingI>();

    [HideInInspector]
    public string phpURL = "http://unitycoc.dothome.co.kr/townLoading.php";
    [HideInInspector]
    public string jsonURL = "http://unitycoc.dothome.co.kr/townLoading.json";
    [HideInInspector]
    public string phpSendURL = "http://unitycoc.dothome.co.kr/saveTown.php";
    [HideInInspector]
    public string phpDelURL = "http://unitycoc.dothome.co.kr/delTown.php";
}
