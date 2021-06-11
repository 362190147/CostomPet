package top.yumesekai.pet

import android.app.ActivityManager
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.net.Uri
import android.os.Build
import android.os.Bundle
import android.provider.Settings
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.Toast
import androidx.annotation.RequiresApi
import androidx.appcompat.app.AppCompatActivity


class PetActivity : AppCompatActivity() {
    //判断权限
    fun commonROMPermissionCheck(context: Context?): Boolean {
        val result = true
        if (Build.VERSION.SDK_INT >= 23) {
            try {
                //Class clazz = Settings.class;
                //Method canDrawOverlays = clazz.getDeclaredMethod("canDrawOverlays", Context.class);
                //result = (Boolean) canDrawOverlays.invoke(null, context);
                return Settings.canDrawOverlays(applicationContext)
            } catch (e: Exception) {
                Log.e(TAG, Log.getStackTraceString(e))
            }
        }
        return result
    }

    //申请权限
    fun requestAlertWindowPermission() {
        val intent = Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION)
        intent.data = Uri.parse("package:$packageName")
        startActivityForResult(intent, REQUEST_CODE)
    }

    @RequiresApi(api = Build.VERSION_CODES.M)  //处理回调
    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (requestCode == REQUEST_CODE) {
            if (Settings.canDrawOverlays(this)) {
                Log.i(TAG, "onActivityResult granted")
            }
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        // TODO Auto-generated method stub
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_pet)
        findViewById<View>(R.id.btn_start_service).setOnClickListener { view ->
            // 开始关闭服务
            val service = Intent(this@PetActivity, FloatService::class.java)
            if (!isServiceRunning(this@PetActivity, FloatService::class.java.name)) {
                val p = arrayOf(Settings.ACTION_MANAGE_OVERLAY_PERMISSION)
                //if( PetActivity.checkPermission1(PetActivity.this, p )){
                if (commonROMPermissionCheck(this@PetActivity)) {
                    (view as Button).text = "关闭"
                    Toast.makeText(this@PetActivity, "有权限", Toast.LENGTH_LONG).show()
                    startService(service)
                } else {
                    Toast.makeText(this@PetActivity, "没权限", Toast.LENGTH_LONG).show()
                    requestAlertWindowPermission()
                }
            } else {
                stopService(service)
                (view as Button).text = "开启"
            }
        }
    }

    companion object {
        private const val REQUEST_CODE = 1
        private const val TAG = "PetActivity"
        fun checkPermission1(context: Context, permissions: Array<String>): Boolean {
            val packageManager = context.packageManager
            val packageName = context.packageName
            for (permission in permissions) {
                val per = packageManager.checkPermission(permission, packageName)
                if (PackageManager.PERMISSION_DENIED == per) {
                    Log.w(TAG, "required permission not granted . permission = $permission")
                    return false
                }
            }
            return true
        }

        /**
         * 用来判断服务是否运行.
         *
         * @param context
         *
         * @param className
         * 判断的服务名字
         * @return true 在运行 false 不在运行
         */
        fun isServiceRunning(context: Context, className: String): Boolean {
            var isRunning = false
            val activityManager = context
                .getSystemService(ACTIVITY_SERVICE) as ActivityManager
            val serviceList = activityManager
                .getRunningServices(200)
            if (serviceList.size <= 0) {
                return false
            }
            for (i in serviceList.indices) {
                if (serviceList[i].service.className == className) {
                    isRunning = true
                    break
                }
            }
            return isRunning
        }
    }
}