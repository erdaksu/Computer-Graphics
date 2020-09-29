using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlatformAvoid : MonoBehaviour
{
    public float LeftPoint = 7.5F;
    public float RightPoint = 17F;
    public int Direction = 1;

    void Update()
    {
        if (Direction == 1)
        {
            transform.Translate(Vector3.right * 4 * Time.deltaTime, Space.World);
            Direction = 1;
        }
        if (this.transform.position.x > RightPoint)
        {
            Direction = 2;
        }

        if (Direction == 2)
        {
            transform.Translate(Vector3.right * -4 * Time.deltaTime, Space.World);
            Direction = 2;
        }
        if (this.transform.position.x < LeftPoint)
        {
            Direction = 1;
        }
    }
}