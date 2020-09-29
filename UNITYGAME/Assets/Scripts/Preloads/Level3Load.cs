using UnityEngine;
using System.Collections;


public class Level3Load : MonoBehaviour
{
    IEnumerator Start()
    {
        yield return new WaitForSeconds(1f);
        Application.LoadLevel(7);
    }
}
