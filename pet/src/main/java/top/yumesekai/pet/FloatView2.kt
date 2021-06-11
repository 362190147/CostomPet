package top.yumesekai.pet

import android.content.Context
import android.graphics.PixelFormat
import android.graphics.Rect
import android.os.Build
import android.util.AttributeSet
import android.util.Log
import android.view.Gravity
import android.view.MotionEvent
import android.view.WindowManager
import androidx.appcompat.widget.AppCompatImageView
import kotlin.math.abs

internal class FloatView2(context: Context, attrs: AttributeSet?) :
    AppCompatImageView(context, attrs) {
    /**触屏点数 */
    private var pointerCount = 0
    private var mWM: WindowManager = context.getSystemService(Context.WINDOW_SERVICE) as WindowManager
    var mWMParams: WindowManager.LayoutParams = WindowManager.LayoutParams()
    private var mTouchX = 0f
    private var mTouchY = 0f
    private var rawStartX = 0f
    private var rawStartY = 0f
    private var mStartX = 0f
    private var mStartY = 0f

    private var moveX=0f
    private var moveY=0f


    override fun onTouchEvent(event: MotionEvent): Boolean {
        //获取到状态栏的高度
        val frame = Rect()
        getWindowVisibleDisplayFrame(frame)
        val statusBarHeight = frame.top
        println("statusBarHeight:$statusBarHeight")
        // 获取相对屏幕的坐标，即以屏幕左上角为原点
        pointerCount=event.pointerCount
        // statusBarHeight是系统状态栏的高度
        mTouchX = event.x
        mTouchY = event.y
        Log.i("tag", "currX${event.rawX}====currY${event.rawY}")
        when (event.action) {
            MotionEvent.ACTION_DOWN -> {
                // 获取相对View的坐标，即以此View左上角为原点
                moveY=0f
                moveX=0f
                rawStartX=event.rawX
                rawStartX=event.rawY
                mStartX = event.rawX
                mStartY = event.rawY
                Log.i("tag", "startX" + mTouchX + "startY" + mTouchY)
            }
            MotionEvent.ACTION_MOVE -> {
                updateViewPosition(event)
            }
            MotionEvent.ACTION_UP -> {
                updateViewPosition(event)
                    mTouchY = 0f
                    mTouchX = 0f
                checkClick(event)
            }
        }
        return true
    }

    private fun checkClick(event: MotionEvent){
        if(abs(rawStartX-event.rawX) <5 && abs(rawStartY-event.rawY) < 5){
            callOnClick()
        }
    }


    private fun updateViewPosition(event: MotionEvent) {
        // 更新浮动窗口位置参数
        moveX=event.rawX-mStartX
        moveY=event.rawY-mStartY
        mStartX=event.rawX
        mStartY=event.rawY
        mWMParams.x += moveX.toInt()
        mWMParams.y += moveY.toInt()

        mWM.updateViewLayout(this, mWMParams) // 刷新显示
    }


    fun initLayoutParams() {
        mWMParams.format = PixelFormat.RGBA_8888
        mWMParams.type = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O)
            WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY else WindowManager.LayoutParams.TYPE_PHONE
        mWMParams.flags = (WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE
                or WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS
                or WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL)
        mWMParams.width = 300 //LayoutParams.MATCH_PARENT;
        mWMParams.height = 300 //LayoutParams.MATCH_PARENT;
        mWMParams.gravity = Gravity.START or Gravity.TOP
    }


    //private GLObjManager GLManager;
    init {
        initLayoutParams()
        background = getContext().getDrawable(R.drawable.bg)
    }
}