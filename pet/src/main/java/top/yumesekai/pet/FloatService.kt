package top.yumesekai.pet

import android.app.NotificationChannel
import android.app.NotificationManager
import android.app.PendingIntent
import android.app.Service
import android.content.Context
import android.content.Intent
import android.os.Build
import android.os.IBinder
import android.util.Log
import android.view.View
import android.view.WindowManager
import android.widget.Toast
import androidx.core.app.NotificationCompat
import androidx.core.app.NotificationManagerCompat

/**
 * 悬浮窗口服务
 */
class FloatService : Service() {
    private val CHANNEL_ID: String="CHANNEL_PET"
    val mWM: WindowManager by lazy {
        getSystemService(WINDOW_SERVICE) as WindowManager
    }
    //private val timer: Timer? = null

    //通知栏
    //var mNotificationManager: NotificationManager? = null
    val notifyId = 998
    var petView: View? = null
    var character: Character? = null
    fun showDebug(msg: String?) {
        Log.d("FloatService", msg!!)
        Toast.makeText(this, msg, Toast.LENGTH_SHORT).show()
    }

    override fun onBind(intent: Intent): IBinder? {
        showDebug("Service onBind")
        return null
    }

    override fun onCreate() {
        showDebug("Service onCraete")
        super.onCreate()
        //mNotificationManager = getSystemService(NOTIFICATION_SERVICE) as NotificationManager
        val floatView = FloatView2(this, null)


        //FloatView floatView = new FloatView(this, null);
        petView = floatView

        //floatView.setWM(mWM)

        mWM.addView(petView, floatView.mWMParams)
        character = Character()

        createNotificationChannel()

        floatView.setOnClickListener {
            pushNotifcation(1, "pet", "life" + character!!.getAttribution("life"))
            Toast.makeText(this,"点击",Toast.LENGTH_SHORT)
        }
    }

    override fun onStartCommand(intent: Intent, flags: Int, startId: Int): Int {
        showDebug("Service onStartCommand")
        return super.onStartCommand(intent, flags, startId)
    }

    override fun onDestroy() {
        mWM.removeView(petView)
        super.onDestroy()
    }

    private fun createNotificationChannel() {
        // Create the NotificationChannel, but only on API 26+ because
        // the NotificationChannel class is new and not in the support library
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            val name = "channel_name"//getString(R.string.channel_name)
            val descriptionText = "channel_description"//getString(R.string.channel_description)
            val importance = NotificationManager.IMPORTANCE_DEFAULT
            val channel = NotificationChannel(CHANNEL_ID, name, importance).apply {
                description = descriptionText
            }
            // Register the channel with the system
            val notificationManager: NotificationManager =
                    getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
            notificationManager.createNotificationChannel(channel)
        }
    }

    /**
     * 发送通知
     * @param title 标题
     * @param text 内容
     */
    fun pushNotifcation(id: Int, title: CharSequence?, text: CharSequence?) {

        val intent = Intent(this, PetActivity::class.java).apply {
            flags = Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_CLEAR_TASK
        }
        val pendingIntent = PendingIntent.getActivity(this, 0, intent, 0)
        var builder = NotificationCompat.Builder(this, CHANNEL_ID)
                .setSmallIcon(R.drawable.ic_launcher)
                .setContentTitle(title)
                .setContentText(text)
                .setPriority(NotificationCompat.PRIORITY_DEFAULT)
                .setContentIntent(pendingIntent)
                .setAutoCancel(true)

        with(NotificationManagerCompat.from(this)) {
            // notificationId is a unique int for each notification that you must define
            notify(id, builder.build())
        }
        /**
         * Intent intent = new Intent(this, FloatService.class);
         * //intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_SINGLE_TOP);
         * PendingIntent contentIntent = PendingIntent.getService(this, 0,
         * intent, PendingIntent.FLAG_UPDATE_CURRENT);
         * Notification.Builder builder = new Notification.Builder(this);
         * builder.setContentIntent(contentIntent)
         * .setSmallIcon(R.drawable.ic_launcher)
         * .setWhen(System.currentTimeMillis()).setAutoCancel(false)
         * .setContentTitle(title).setContentText(text);
         * //startForeground(id, builder.getNotification());
         * mNotificationManager.notify(id, builder.build()); */
    }
}