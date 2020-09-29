using UnityEngine;
using System.Collections;


public class Level2Load : MonoBehaviour
{
    IEnumerator Start()
    {
        yield return new WaitForSeconds(1f);
        Application.LoadLevel(5);
    }
}
