using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlatformAvoid1 : MonoBehaviour
{
    public float LeftPoint = 6F;
    public float RightPoint = 9.5F;
    public int Direction = 1;

    void Update()
    {
        if (Direction == 6)
        {
            transform.Translate(Vector3.right * 4 * Time.deltaTime, Space.World);
            Direction = 6;
        }
        if (this.transform.position.x > RightPoint)
        {
            Direction = 7;
        }

        if (Direction == 7)
        {
            transform.Translate(Vector3.right * -4 * Time.deltaTime, Space.World);
            Direction = 7;
        }
        if (this.transform.position.x < LeftPoint)
        {
            Direction = 6;
        }
    }
}