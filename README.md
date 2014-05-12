Native app & cocos2d-x integration scafold
=========

Android and Cocos2D-x integration scafold for testing purpouses.

> What it does:
> 
> This is a test Cocos2D-x app that runs inside another Android App.
> When you click the button, the Android native app writes a file on /data/data/package/files/ folder with some data on it. The Coco2D-x app that get launched will read this file and show it on a CCLabelText. This scafold also includes Backbutton implementation for killing the Cocos2D-x part of the application.

Begin integration:
--------

Start by creating a Cocos2D-X project.


```
    // Create project
    asier:~ $ cocos new MyCocosGame -p com.irontec.axierjhtz -l cpp -d ~/Desktop/CocosGame
```



Import libcocos2dx

```
    MyCocosGame/cocos2d/cocos/2d/platform/java/
```

If using Eclipse, importing MyCocosGame could help making things more easy.


Copy <b>org.cocos2dx.cpp</b> package to your Android project


Modify <b>AppActivity.java</b>

```
	package org.cocos2dx.cpp;

	import org.cocos2dx.lib.Cocos2dxActivity;
	import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

	public class AppActivity extends Cocos2dxActivity {

		public Cocos2dxGLSurfaceView onCreateView() {
			Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
			glSurfaceView.setEGLConfigChooser(5,6,5,0,16,8);
			return glSurfaceView;
		}
	}
```

Modify you <b>MainActivity.java</b> to write params on a file.

```
    // This function will write a .txt file 
    // in /data/data/package/files/ folder
    public void writeToInternalFilesDir(String filename) {
		JSONObject obj = new JSONObject();
		try {
			obj.put("1", "Hello World");
		} catch (JSONException e1) {
			e1.printStackTrace();
		}
		
		BufferedWriter writer;
		try {
			File path = new File(getActivity().getFilesDir(), filename);
			writer = new BufferedWriter(new FileWriter(path));
			writer.write(obj.toString());
			writer.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
```

Navigate to <b>YouFolder/CocosGame/MyCocosGame/Classes/</b> and modify <b>HelloWorldScene.cpp</b> to add the parameter interceptor.

```
    // This snippet reads a file located 
    // in /data/data/package/files/ folder
    std::string path = CCFileUtils::getInstance()->getWritablePath() + "gane_data.txt";
    FILE *fp = fopen(path.c_str(), "r");
    std::char buf[200] = {0};

    if (! fp)
    {
        CCLOG("can not open file %s", path.c_str());
    } else {
        fgets(buf, 200, fp);
        CCLOG("read content %s", buf);
    }
```

Now compile everything and run the app standalone to see if the code it´s Ok.

```
    asier:~ $ cocos run -s ~/Desktop/CocosGame/MyCocosGame/ -p android
```

After compiling the project check if everithing is ok and then refresh every project on Eclipse just to make sure all changes have been applied.

Copy <b>jni</b>, <b>obj</b> folders to your project root

Copy <b>assets</b> folder content to your project assets folder.

From <b>bin</b> directory copy <b>dexedLibs, classes.dex, classes.dex.d, all .apk, apk.d, ap and ap_.d files</b>.

From <b>libs</b> folder copy all the <b>armeabi</b> folder to your project libs folder.

Modify your projects <b>AndroidManifest.xml</b> file so you can add the <b>AppActivity</b> activity. Remenber to remove the intent filters for this activity. Add the <b>glEsVersion</b>.

Run and test (AVD with <b>armeabi</b> config).

Backbutton implementation
----

For implementing Backbutton functionality you need to modifiy <b>Cocos2dxGLSurfaceView.java</b>

```
    //...
        private Cocos2dxActivity mActivity;
    //...

    //...
    
        // ===========================================================
        // Constructors
        // ===========================================================
        public Cocos2dxGLSurfaceView(final Activity activity) {
                super(activity.getBaseContext());
                this.mActivity = (Cocos2dxActivity) activity;
                this.initView();
        }
    // ...
 

    // ...
        @Override
        public boolean onKeyDown(final int pKeyCode, final KeyEvent pKeyEvent) {
                switch (pKeyCode) {
                case KeyEvent.KEYCODE_BACK:
                        if (mActivity != null && !mActivity.isFinishing()) {
                                mActivity.finish();
                        }
                case KeyEvent.KEYCODE_MENU:
                        this.queueEvent(new Runnable() {
                                @Override
                                public void run() {
                                        Cocos2dxGLSurfaceView.this.mCocos2dxRenderer.handleKeyDown(pKeyCode);
                                }
                        });
                        return true;
                default:
                        return super.onKeyDown(pKeyCode, pKeyEvent);
                }
        }

    // ...
```

This should do the work.

License
----

The MIT License (MIT)

Copyright (c) 2014 Asier

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


**Free Software, Hell Yeah!**