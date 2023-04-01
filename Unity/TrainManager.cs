using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TrainManager : MonoBehaviour
{
    csPlayerInfo playerInfo;
    Transform camp;
    GameObject parent;

    public Text txtSoldier;
    public Text txtArcher;
    public Text txtKnight;
    public Text txtHorseArcher;
    public Text txtCleric;
    public Text txtWizard;
    public Text txtCatapult;

    void Start()
    {
        playerInfo = GameObject.FindWithTag("Player").GetComponent<csPlayerInfo>();
        parent = GameObject.FindWithTag("UNITS");
    }

    void Update()
    {
        txtSoldier.text      = "보유량 : " + playerInfo.armyManager.units.Find(u => u.name.Contains("soldier")).num;
        txtArcher.text       = "보유량 : " + playerInfo.armyManager.units.Find(u => u.name.Contains("archer")).num ;
        txtKnight.text       = "보유량 : " + playerInfo.armyManager.units.Find(u => u.name.Contains("knight")).num;
        txtHorseArcher.text = "보유량 : " + playerInfo.armyManager.units.Find(u => u.name.Contains("horsearcher")).num; 
        txtCleric.text       = "보유량 : " + playerInfo.armyManager.units.Find(u => u.name.Contains("cleric")).num;
        txtWizard.text       = "보유량 : " + playerInfo.armyManager.units.Find(u => u.name.Contains("wizard")).num;
        txtCatapult.text     = "보유량 : " + playerInfo.armyManager.units.Find(u => u.name.Contains("catapult")).num;
    }

    public void StartCoroutineTrain(UnitMENU unit)
    {
        StartCoroutine("Train", unit);
    }

    IEnumerator Train(UnitMENU unit)
    {
        playerInfo.mana -= unit.mana;
        playerInfo.armyManager.units.Find(u => u.name.Contains(unit.objectName)).num++;

        yield return new WaitForSeconds(unit.trainTime);

        GameObject trainedUnit = Instantiate(unit.unitPrefab, parent.transform.position, Quaternion.identity);
        trainedUnit.transform.SetParent(parent.transform);
    }
}
