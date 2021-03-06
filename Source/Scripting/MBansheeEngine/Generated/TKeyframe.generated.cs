using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Animation
	 *  @{
	 */

	/// <summary>Animation keyframe, represented as an endpoint of a cubic hermite spline.</summary>
	[StructLayout(LayoutKind.Sequential), SerializeObject]
	public partial struct KeyFrame
	{
		/// <summary>Value of the key.</summary>
		public float value;
		/// <summary>Input tangent (going from the previous key to this one) of the key.</summary>
		public float inTangent;
		/// <summary>Output tangent (going from this key to next one) of the key.</summary>
		public float outTangent;
		/// <summary>Position of the key along the animation spline.</summary>
		public float time;
	}

	/** @} */

	/** @addtogroup Animation
	 *  @{
	 */

	/// <summary>Animation keyframe, represented as an endpoint of a cubic hermite spline.</summary>
	[StructLayout(LayoutKind.Sequential), SerializeObject]
	public partial struct KeyFrameVec3
	{
		/// <summary>Value of the key.</summary>
		public Vector3 value;
		/// <summary>Input tangent (going from the previous key to this one) of the key.</summary>
		public Vector3 inTangent;
		/// <summary>Output tangent (going from this key to next one) of the key.</summary>
		public Vector3 outTangent;
		/// <summary>Position of the key along the animation spline.</summary>
		public float time;
	}

	/** @} */

	/** @addtogroup Animation
	 *  @{
	 */

	/// <summary>Animation keyframe, represented as an endpoint of a cubic hermite spline.</summary>
	[StructLayout(LayoutKind.Sequential), SerializeObject]
	public partial struct KeyFrameQuat
	{
		/// <summary>Value of the key.</summary>
		public Quaternion value;
		/// <summary>Input tangent (going from the previous key to this one) of the key.</summary>
		public Quaternion inTangent;
		/// <summary>Output tangent (going from this key to next one) of the key.</summary>
		public Quaternion outTangent;
		/// <summary>Position of the key along the animation spline.</summary>
		public float time;
	}

	/** @} */
}
