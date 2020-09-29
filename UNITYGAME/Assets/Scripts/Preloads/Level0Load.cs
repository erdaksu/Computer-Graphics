using UnityEngine;
using System.Collections;


public class Level0Load : MonoBehaviour
{
    IEnumerator Start()
    {
        yield return new WaitForSeconds(1f);
        Application.LoadLevel(2);
    }
}
