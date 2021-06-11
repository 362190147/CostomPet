package top.yumesekai.pet;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;

import androidx.annotation.Nullable;

public class PetService extends Service {
    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }


    private static final String TAG = "FBService";
    public static final int TYPE_ADD = 0;
    public static final int TYPE_DEL = 1;


    @Override
    public void onCreate() {
        super.onCreate();
        Log.d(TAG,"onCreate");

    }


    private void showFloatBall() {
        Log.d(TAG,"showFloatBall");

    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.d(TAG,"onDestroy");

    }

}
