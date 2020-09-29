using UnityEngine;
using System.Collections;

public class EndScript1 : MonoBehaviour
{
    public AudioSource Won;
    IEnumerator OnTriggerEnter(Collider col)
    {
        Won.Play();
        yield return new WaitForSeconds(1f);
        Application.LoadLevel(6);
    }
}