using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Animation
	 *  @{
	 */

	/// <summary>
	/// Animation spline represented by a set of keyframes, each representing an endpoint of a cubic hermite curve. The spline 
	/// can be evaluated at any time, and uses caching to speed up multiple sequential evaluations.
	/// </summary>
	public partial class AnimationCurve : ScriptObject
	{
		private AnimationCurve(bool __dummy0) { }
		protected AnimationCurve() { }

		/// <summary>Creates a new animation curve.</summary>
		/// <param name="keyframes">Keyframes to initialize the curve with. They must be sorted by time.</param>
		public AnimationCurve(KeyFrame[] keyframes)
		{
			Internal_TAnimationCurve(this, keyframes);
		}

		/// <summary>Returns a list of all keyframes in the curve.</summary>
		public KeyFrame[] KeyFrames
		{
			get { return Internal_getKeyFrames(mCachedPtr); }
		}

		/// <summary>
		/// Evaluate the animation curve at the specified time. If evaluating multiple values in a sequential order consider 
		/// using the cached version of evaluate() for better performance.
		/// </summary>
		/// <param name="time">%Time to evaluate the curve at.</param>
		/// <param name="loop">
		/// If true the curve will loop when it goes past the end or beggining. Otherwise the curve  value will be clamped.
		/// </param>
		/// <returns>Interpolated value from the curve at provided time.</returns>
		public float Evaluate(float time, bool loop = true)
		{
			return Internal_evaluate(mCachedPtr, time, loop);
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_TAnimationCurve(AnimationCurve managedInstance, KeyFrame[] keyframes);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern float Internal_evaluate(IntPtr thisPtr, float time, bool loop);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern KeyFrame[] Internal_getKeyFrames(IntPtr thisPtr);
	}

	/** @} */

	/** @addtogroup Animation
	 *  @{
	 */

	/// <summary>
	/// Animation spline represented by a set of keyframes, each representing an endpoint of a cubic hermite curve. The spline 
	/// can be evaluated at any time, and uses caching to speed up multiple sequential evaluations.
	/// </summary>
	public partial class Vector3Curve : ScriptObject
	{
		private Vector3Curve(bool __dummy0) { }
		protected Vector3Curve() { }

		/// <summary>Creates a new animation curve.</summary>
		/// <param name="keyframes">Keyframes to initialize the curve with. They must be sorted by time.</param>
		public Vector3Curve(KeyFrameVec3[] keyframes)
		{
			Internal_TAnimationCurve(this, keyframes);
		}

		/// <summary>Returns a list of all keyframes in the curve.</summary>
		public KeyFrameVec3[] KeyFrames
		{
			get { return Internal_getKeyFrames(mCachedPtr); }
		}

		/// <summary>
		/// Evaluate the animation curve at the specified time. If evaluating multiple values in a sequential order consider 
		/// using the cached version of evaluate() for better performance.
		/// </summary>
		/// <param name="time">%Time to evaluate the curve at.</param>
		/// <param name="loop">
		/// If true the curve will loop when it goes past the end or beggining. Otherwise the curve  value will be clamped.
		/// </param>
		/// <returns>Interpolated value from the curve at provided time.</returns>
		public Vector3 Evaluate(float time, bool loop = true)
		{
			Vector3 temp;
			Internal_evaluate(mCachedPtr, time, loop, out temp);
			return temp;
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_TAnimationCurve(Vector3Curve managedInstance, KeyFrameVec3[] keyframes);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_evaluate(IntPtr thisPtr, float time, bool loop, out Vector3 __output);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern KeyFrameVec3[] Internal_getKeyFrames(IntPtr thisPtr);
	}

	/** @} */

	/** @addtogroup Animation
	 *  @{
	 */

	/// <summary>
	/// Animation spline represented by a set of keyframes, each representing an endpoint of a cubic hermite curve. The spline 
	/// can be evaluated at any time, and uses caching to speed up multiple sequential evaluations.
	/// </summary>
	public partial class QuaternionCurve : ScriptObject
	{
		private QuaternionCurve(bool __dummy0) { }
		protected QuaternionCurve() { }

		/// <summary>Creates a new animation curve.</summary>
		/// <param name="keyframes">Keyframes to initialize the curve with. They must be sorted by time.</param>
		public QuaternionCurve(KeyFrameQuat[] keyframes)
		{
			Internal_TAnimationCurve(this, keyframes);
		}

		/// <summary>Returns a list of all keyframes in the curve.</summary>
		public KeyFrameQuat[] KeyFrames
		{
			get { return Internal_getKeyFrames(mCachedPtr); }
		}

		/// <summary>
		/// Evaluate the animation curve at the specified time. If evaluating multiple values in a sequential order consider 
		/// using the cached version of evaluate() for better performance.
		/// </summary>
		/// <param name="time">%Time to evaluate the curve at.</param>
		/// <param name="loop">
		/// If true the curve will loop when it goes past the end or beggining. Otherwise the curve  value will be clamped.
		/// </param>
		/// <returns>Interpolated value from the curve at provided time.</returns>
		public Quaternion Evaluate(float time, bool loop = true)
		{
			Quaternion temp;
			Internal_evaluate(mCachedPtr, time, loop, out temp);
			return temp;
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_TAnimationCurve(QuaternionCurve managedInstance, KeyFrameQuat[] keyframes);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_evaluate(IntPtr thisPtr, float time, bool loop, out Quaternion __output);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern KeyFrameQuat[] Internal_getKeyFrames(IntPtr thisPtr);
	}

	/** @} */
}
