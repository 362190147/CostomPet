package top.yumesekai.pet;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;


import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.pm.Signature;
import android.content.res.AssetManager;
import android.graphics.PixelFormat;
import android.graphics.Rect;
import android.opengl.GLSurfaceView;
import android.opengl.GLSurfaceView.Renderer;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;
/**
 * 悬浮窗口类
 * @author wei
 *
 */
public class FloatView extends GLSurfaceView implements Renderer {

	static {
		System.loadLibrary("pet");
	}

	public native String stringFromJNI();
	public native void drawC();

	public native void onCreateC(AssetManager assetManager);
	public native void onChangeC(int width, int height);
	public native void onDestroyC();
	public native void onTouchC();

	private WindowManager mWM = null;
	public WindowManager.LayoutParams mWMParams = null;


	/**触屏点数*/
	private int pointerCount=0;
	//private GLObjManager GLManager;

	public FloatView(Context context, AttributeSet attrs) {
		super(context, attrs);

		initLayoutParams();

		setEGLContextClientVersion(1);
		setZOrderOnTop(true);
		//设定为透明
		setEGLConfigChooser(8, 8, 8, 8, 16, 0);

		getHolder().setFormat(PixelFormat.TRANSLUCENT);
		setRenderer(this);
	}



	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		onCreateC(getContext().getAssets());
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		onChangeC(width, height);
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
			Log.i("tag", "surfaceDestroyed");
		onDestroyC();
		super.surfaceDestroyed(holder);
	}

	@Override
	public void onDrawFrame(GL10 gl) {
		drawC();
	}

	private float mTouchX;
	private float mTouchY;
	private float x;
	private float y;
	private float mStartX;
	private float mStartY;
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		//获取到状态栏的高度
		Rect frame = new Rect();
		getWindowVisibleDisplayFrame(frame);
		int statusBarHeight = frame.top;
		System.out.println("statusBarHeight:"+statusBarHeight);
		// 获取相对屏幕的坐标，即以屏幕左上角为原点
		x = event.getRawX();
		y = event.getRawY(); // statusBarHeight是系统状态栏的高度

		Log.i("tag", "currX" + x + "====currY" + y);

		switch (event.getAction()) {
		case MotionEvent.ACTION_DOWN: // 捕获手指触摸按下动作
		// 获取相对View的坐标，即以此View左上角为原点
		mTouchX = event.getX();
		mTouchY = event.getY();
		mStartX = x;
		mStartY = y;

		Log.i("tag", "startX" + mTouchX + "====startY" + mTouchY);

		break;
		case MotionEvent.ACTION_MOVE: // 捕获手指触摸移动动作
		updateViewPosition();
		mTouchX = event.getX();
		mTouchY = event.getY();
		break;
		case MotionEvent.ACTION_UP: // 捕获手指触摸离开动作
		updateViewPosition();
		mTouchX = mTouchY = 0;
		if ((x - mStartX) < 5 && (y - mStartY) < 5) {
		 }
		break;
		}

		return true;
	}

	private void updateViewPosition() {
		// 更新浮动窗口位置参数
		mWMParams.x += (int) (x - mStartX );
		mWMParams.y += (int) (y - mStartY );
		mStartX=x;
		mStartY=y;
		mWM.updateViewLayout(this, mWMParams); // 刷新显示

	}

	public void setWM(WindowManager wm){
		mWM=wm;
	}

	public void initLayoutParams(){
		mWMParams			= new WindowManager.LayoutParams();
		mWMParams.format	= PixelFormat.RGBA_8888;
		mWMParams.type		= LayoutParams.TYPE_PHONE;
		mWMParams.flags		= LayoutParams.FLAG_NOT_FOCUSABLE
						    | LayoutParams.FLAG_LAYOUT_NO_LIMITS
						    | LayoutParams.FLAG_NOT_TOUCH_MODAL;

		mWMParams.width 	= 300;//LayoutParams.MATCH_PARENT;
		mWMParams.height 	= 300;//LayoutParams.MATCH_PARENT;
		mWMParams.gravity   =  Gravity.LEFT | Gravity.TOP;
	}

	void drawBallom(){
	}

	@Override
	protected void finalize() throws Throwable {
		onDestroyC();
		super.finalize();
	}

	//获得签名哈希值
	int getHash(Context context){
		int code=0;
		final String packname = context.getPackageName();
		PackageInfo packageInfo = null;
		try {
			packageInfo = context.getPackageManager().getPackageInfo(packname, PackageManager.GET_SIGNATURES);
			Signature[] signs = packageInfo.signatures;
			Signature sign = signs[0];
			code = sign.hashCode();
			Log.i("tag", "签名哈希"+code);

		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}
		return code;
	}
}
