package com.example.freedom;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    /**
     *
     *    Button button=(Button)findViewById(R.id.button);
     *    button.setOnClickListener(this);
     *    }
     * @Override
     * public void OnClick(View v){
     * switch (v.getId()){
     * case R.id.button:
     * //在此处添加逻辑
     *     break;
     * default:
     *     break;
     *         }
     *     }
     * }

     * **/

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//        stringFromJNI()
        // Example of a call to a native method


        Button btn = (Button)  findViewById(R.id.button);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                TextView tv = MainActivity.this.findViewById(R.id.sample_text);
                tv.setText(MyJni.testGo());


                Toast tot = Toast.makeText(
                        MainActivity.this,
                        "匿名内部类实现button点击事件",
                        Toast.LENGTH_LONG);
                tot.show();
            }
        });
    }
    @Override
    protected void onDestroy(){
        super.onDestroy();
        //mObj.release();
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
