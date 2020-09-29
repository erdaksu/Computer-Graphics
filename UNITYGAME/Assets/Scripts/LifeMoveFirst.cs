using UnityEngine;
using System.Collections;

public class LifeMoveFirst : MonoBehaviour
{
    public GameObject ActualLife;
    public GameObject ThisLife;

    void Update()
    {
        transform.parent = null;
        transform.Translate(Vector3.up * 2 * Time.deltaTime, Space.World);
        StartCoroutine(CloseAnim());
    }

    IEnumerator CloseAnim()
    {
        yield return new WaitForSeconds(0.1f);
        ActualLife.SetActive(true);
        ThisLife.SetActive(false);
    }

}