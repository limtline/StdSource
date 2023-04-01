using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.SceneManagement;
using UnityEngine.Networking;

public class csPlayerInfo : MonoBehaviour
{
    [HideInInspector]
    public TownManager townManager;
    [HideInInspector]
    public ArmyManager armyManager;
    [HideInInspector]
    public ResourceManager resourceManager;

    public string id;
    public string pName;
    public bool townLoaded;

    public int gold;
    public int mana;
    public int emerald;

    void Awake()
    {
        DontDestroyOnLoad(gameObject);

        townManager     = gameObject.GetComponent<TownManager>();
        armyManager     = gameObject.GetComponent<ArmyManager>();
        resourceManager = gameObject.GetComponent<ResourceManager>();

        armyManager.enabled = false;
    }

    void Update()
    {
        if (SceneManager.GetActiveScene().name == "scPlay")
        {
            if (!townLoaded)
            {
                GameObject tmp;
                GameObject parent = GameObject.FindGameObjectWithTag("HOME");
                BattleManager battleManager = GameObject.Find("BattleManager").GetComponent<BattleManager>();
                battleManager.id = id;

                Debug.Log(townManager.buildings.Count);
                for (int i = 0; i < townManager.buildings.Count; i++)
                {
                    tmp = Resources.Load<GameObject>("BattleVillage/Prefabs/"+ townManager.buildings[i].name);
                    Vector3 pos = new Vector3(townManager.buildings[i].x, 0, townManager.buildings[i].z);

                    var obj = Instantiate(tmp);

                    obj.AddComponent<Rigidbody>();
                    obj.GetComponent<Rigidbody>().useGravity  = false;
                    obj.GetComponent<Rigidbody>().isKinematic = true;
                    
                    Debug.Log(townManager.buildings[i].name);
                    obj.transform.parent = parent.transform;
                    obj.transform.localPosition = pos;
                }

                townLoaded = true;
            }

            

        }

            if (Input.GetKeyDown(KeyCode.Escape))
            {
                Debug.Log("Escape");
                GetTownLayout();
                EndGame();
            }
    }

    void GetTownLayout()
    {
        if (townManager.buildings != null)
        {
            townManager.buildings.RemoveRange(0, townManager.buildings.Count);
        }

        GameObject built; 
        built = GameObject.FindWithTag("HOME");
        
        foreach (Transform t in built.transform)
        {
            BuildingI building = new BuildingI();
            building.name = t.gameObject.name.Substring(0, t.gameObject.name.Length - 7);
            building.x    = ((int)t.localPosition.x);
            building.z    = ((int)t.localPosition.z);

            Debug.Log("name : " + building.name + "  x : " + building.x + "  z : " + building.z);
            townManager.buildings.Add(building);
        }
    }

    void EndGame()
    {
        StartCoroutine("SaveResource");
        Application.Quit();
    }

    public void SaveGame()
    {
        StartCoroutine("SaveResource");
    }

    IEnumerator SaveResource()
    {
        WWWForm form = new WWWForm();
        form.AddField("id", id);
        form.AddField("gold", gold);
        form.AddField("mana", mana);
        form.AddField("emerald", emerald);

        using (var www = UnityWebRequest.Post(resourceManager.phpSendURL, form))
        {
            yield return www.SendWebRequest();

            if (www.isNetworkError || www.isHttpError)
            {
                Debug.Log(www.error);
            }
            else
            {
                Debug.Log($"id={id}, gold={gold}, mana={mana}, emerald={emerald}");
                Debug.Log("Resource Saved!");
                StartCoroutine("DelTown");
            }
        }
    }

    IEnumerator DelTown()
    {
        WWWForm form = new WWWForm();
        form.AddField("id", id);
        using (var www = UnityWebRequest.Post(townManager.phpDelURL, form))
        {
            yield return www.SendWebRequest();

            if (www.isNetworkError || www.isHttpError)
            {
                Debug.Log(www.error);
            }
            else
            {
                StartCoroutine("SaveTown");
            }
        }
    }

    IEnumerator SaveTown()
    {
        for (int i = 0; i < townManager.buildings.Count; i++)
        {
            WWWForm form1 = new WWWForm();
            form1.AddField("id", id);
            form1.AddField("name", townManager.buildings[i].name);
            form1.AddField("x", townManager.buildings[i].x);
            form1.AddField("z", townManager.buildings[i].z);

            using (var www = UnityWebRequest.Post(townManager.phpSendURL, form1))
            {
                yield return www.SendWebRequest();

                if (www.isNetworkError || www.isHttpError)
                {
                    Debug.Log(www.error);
                }
            }
        }

        StartCoroutine("SaveArmy");
    }

    IEnumerator SaveArmy()
    {
        for (int i = 0; i < armyManager.units.Count; i++)
        {
            WWWForm form1 = new WWWForm();
            form1.AddField("id", id);
            form1.AddField("name",  armyManager.units[i].name);
            form1.AddField("level", armyManager.units[i].level);
            form1.AddField("num",   armyManager.units[i].num);

            using (var www = UnityWebRequest.Post(armyManager.phpSendURL, form1))
            {
                yield return www.SendWebRequest();

                if (www.isNetworkError || www.isHttpError)
                {
                    Debug.Log(www.error);
                }
            }
        }

        Debug.Log("save complete");
    }
}
