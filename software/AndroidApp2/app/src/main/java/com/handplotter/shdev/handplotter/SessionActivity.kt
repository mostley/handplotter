package com.handplotter.shdev.handplotter

import android.content.Context
import android.content.Intent
import android.content.res.Configuration.ORIENTATION_PORTRAIT
import android.net.Uri
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.support.constraint.ConstraintLayout
import android.util.Log
import android.view.*
import android.widget.FrameLayout
import com.caverock.androidsvg.SVG
import com.caverock.androidsvg.SVGImageView
import org.opencv.android.CameraBridgeViewBase
import org.opencv.core.Mat
import org.opencv.android.LoaderCallbackInterface
import org.opencv.android.BaseLoaderCallback
import org.opencv.android.OpenCVLoader
import org.opencv.core.Core
import org.opencv.core.CvType
import org.opencv.imgproc.Imgproc

import org.opencv.aruco.Aruco
import org.opencv.aruco.Dictionary

class SessionActivity : AppCompatActivity(), CameraBridgeViewBase.CvCameraViewListener2 {
    private var fullscreenContent: ConstraintLayout? = null
    private val mHideHandler = Handler()
    private val mHidePart2Runnable = Runnable {
        // Delayed removal of status and navigation bar

        // Note that some of these constants are new as of API 16 (Jelly Bean)
        // and API 19 (KitKat). It is safe to use them, as they are inlined
        // at compile-time and do nothing on earlier devices.
        fullscreenContent!!.systemUiVisibility =
                View.SYSTEM_UI_FLAG_LOW_PROFILE or
                View.SYSTEM_UI_FLAG_FULLSCREEN or
                View.SYSTEM_UI_FLAG_LAYOUT_STABLE or
                View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY or
                View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION or
                View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
    }

    // Used for logging success or failure messages
    private val TAG = "SessionActivity"

    // Loads camera view of OpenCV for us to use. This lets us see using OpenCV
    private var openCvCameraView: CameraBridgeViewBase? = null

    // Used in Camera selection from menu (when implemented)
    private val isJavaCamera = true
    private val itemSwitchCamera: MenuItem? = null

    // These variables are used (at the moment) to fix camera orientation from 270degree to 0degree
    private var rgba: Mat? = null
    private var rgbaF: Mat? = null
    private var rgbaT: Mat? = null

    private var markerIds: Mat? = null
    private var dictionary: Dictionary? = null
    private var corners: List<Mat> = ArrayList()

    private val loaderCallback = object : BaseLoaderCallback(this) {
        override fun onManagerConnected(status: Int) {
            when (status) {
                LoaderCallbackInterface.SUCCESS -> {
                    Log.i(TAG, "OpenCV loaded successfully")
                    openCvCameraView!!.enableView()

                    dictionary = Aruco.getPredefinedDictionary(Aruco.DICT_6X6_250);
                    markerIds = Mat()
                }
                else -> {
                    super.onManagerConnected(status)
                }
            }
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        Log.i(TAG, "called onCreate");
        super.onCreate(savedInstanceState)

        window.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        setContentView(R.layout.activity_session)

        val imageUri = Uri.parse(intent.getStringExtra(INTENT_IMAGE_URI))
        requireNotNull(imageUri) { "no imageUri provided in Intent extras" }

        val pos_x = intent.getIntExtra(INTENT_DESIGN_POS_X, 0)

        val pos_y = intent.getIntExtra(INTENT_DESIGN_POS_Y, 0)

        val scale = intent.getFloatExtra(INTENT_DESIGN_SCALE, 1f)

        supportActionBar?.setDisplayHomeAsUpEnabled(true)

        val inputStream = contentResolver.openInputStream(imageUri)
        val svg = SVG.getFromInputStream(inputStream)

        val imageView = SVGImageView(this)
        imageView.setSVG(svg)
        imageView.layoutParams = ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT)

        val layoutContainer = findViewById<FrameLayout>(R.id.layoutContainer)
        //layoutContainer!!.addView(imageView)

        fullscreenContent = findViewById(R.id.fullscreen_content)

        openCvCameraView = findViewById(R.id.cameraSurface);
        openCvCameraView!!.visibility = SurfaceView.VISIBLE;
        openCvCameraView!!.setCvCameraViewListener(this);
    }

    public override fun onPause() {
        super.onPause()
        if (openCvCameraView != null) {
            openCvCameraView!!.disableView()
        }
    }

    public override fun onResume() {
        super.onResume()
        if (!OpenCVLoader.initDebug()) {
            Log.d(TAG, "Internal OpenCV library not found. Using OpenCV Manager for initialization")
            OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_3_0_0, this, loaderCallback)
        } else {
            Log.d(TAG, "OpenCV library found inside package. Using it!")
            loaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS)
        }
    }

    public override fun onDestroy() {
        super.onDestroy()
        if (openCvCameraView != null) {
            openCvCameraView!!.disableView()
        }
    }

    override fun onPostCreate(savedInstanceState: Bundle?) {
        super.onPostCreate(savedInstanceState)

        hide()
    }

    private fun hide() {
        // Hide UI first
        supportActionBar?.hide()

        // Schedule a runnable to remove the status and navigation bar after a delay
        mHideHandler.postDelayed(mHidePart2Runnable, UI_ANIMATION_DELAY.toLong())
    }

    override fun onCameraViewStarted(width: Int, height: Int) {
        rgba = Mat(height, width, CvType.CV_8UC4)
        rgbaF = Mat(height, width, CvType.CV_8UC4)
        rgbaT = Mat(width, width, CvType.CV_8UC4)
    }
    override fun onCameraViewStopped() {
        rgba!!.release();
    }

    override fun onCameraFrame(inputFrame: CameraBridgeViewBase.CvCameraViewFrame?): Mat {
        //rgba = inputFrame!!.rgba()

        val inputImage: Mat = inputFrame!!.gray()

        Aruco.detectMarkers(inputImage, dictionary, corners, markerIds)

        Aruco.drawDetectedMarkers(inputImage, corners)

        if (windowManager.defaultDisplay.rotation == Surface.ROTATION_0) {
            Core.transpose(inputImage, rgbaT)
            Imgproc.resize(rgbaT, rgbaF, inputImage.size(), 0.0, 0.0, 0)
            Core.flip(rgbaF, inputImage, 1)
        } else if (windowManager.defaultDisplay.rotation == Surface.ROTATION_270) {
            Imgproc.resize(inputImage, rgbaF, inputImage.size(), 0.0, 0.0, 0)
            Core.flip(rgbaF, inputImage, -1)
        } else if (windowManager.defaultDisplay.rotation == Surface.ROTATION_90) {
            Imgproc.resize(inputImage, rgbaF, inputImage.size(), 0.0, 0.0, 0)
            Core.flip(rgbaF, inputImage, 1)
        }

        return inputImage;
    }


    companion object {
        /**
         * Some older devices needs a small delay between UI widget updates
         * and a change of the status and navigation bar.
         */
        private const val UI_ANIMATION_DELAY = 300

        private const val INTENT_IMAGE_URI = "image_uri"
        private const val INTENT_DESIGN_POS_X = "design_pos_x"
        private const val INTENT_DESIGN_POS_Y = "design_pos_y"
        private const val INTENT_DESIGN_SCALE = "design_scale"

        fun newIntent(context: Context, image: Uri, pos_x: Int, pos_y: Int, scale: Float): Intent {
            val intent = Intent(context, SessionActivity::class.java)
            intent.putExtra(INTENT_IMAGE_URI, image.toString())
            intent.putExtra(INTENT_DESIGN_POS_X, pos_x)
            intent.putExtra(INTENT_DESIGN_POS_Y, pos_y)
            intent.putExtra(INTENT_DESIGN_SCALE, scale)
            return intent
        }
    }
}
