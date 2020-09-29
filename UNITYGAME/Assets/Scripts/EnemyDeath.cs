using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyDeath : MonoBehaviour
{

    public GameObject Enemy;

    IEnumerator OnTriggerEnter(Collider col)
    {
        this.GetComponent<BoxCollider>().enabled = false;
        Enemy.GetComponent<EnemyMove>().enabled = false;
        Enemy.transform.localScale -= new Vector3(0, 0, 0.8F);
        Enemy.transform.localPosition -= new Vector3(0, 0, 0.4F);
        yield return new WaitForSeconds(1);
        Enemy.transform.position = new Vector3(0, -1000, 0);
    }
}