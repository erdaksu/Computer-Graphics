using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AlienDeath : MonoBehaviour
{

    public GameObject Alien;


    IEnumerator OnTriggerEnter(Collider col)
    {
        this.GetComponent<AlienDeath>().enabled = false;
        Alien.GetComponent<AlienMove>().enabled = false;
        Alien.transform.localScale -= new Vector3(0, 0, 0.8F);
        Alien.transform.localPosition -= new Vector3(0, 0, 0.4F);
        yield return new WaitForSeconds(0);
        Alien.transform.position = new Vector3(0, -1000, 0);

    }
}