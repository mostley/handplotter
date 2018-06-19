package com.handplotter.shdev.handplotter

import android.Manifest
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.net.Uri
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.constraint.ConstraintLayout
import com.caverock.androidsvg.SVG
import android.view.ViewGroup
import com.caverock.androidsvg.SVGImageView
import android.view.ScaleGestureDetector
import android.view.MotionEvent
import android.view.MotionEvent.INVALID_POINTER_ID
import android.widget.RelativeLayout
import android.support.design.widget.FloatingActionButton
import android.support.v4.app.ActivityCompat
import android.support.v4.content.ContextCompat
import android.view.View


class PreparationActivity : AppCompatActivity() {
    private var layoutContainer: ConstraintLayout? = null;
    private var imageView: SVGImageView? = null
    private var scale = 1f
    private var detector: ScaleGestureDetector? = null
    private var activePointerId = INVALID_POINTER_ID
    private var lastTouchX: Float = 0f
    private var lastTouchY: Float = 0f
    private var posX: Int = 0
    private var posY: Int = 0
    private var imageUri: Uri? = null

    companion object {
        private const val INTENT_IMAGE_URI = "image_uri"

        fun newIntent(context: Context, image: Uri): Intent {
            val intent = Intent(context, PreparationActivity::class.java)
            intent.putExtra(INTENT_IMAGE_URI, image.toString())
            return intent
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_preparation)

        val acceptDesignButton = findViewById<FloatingActionButton>(R.id.acceptDesignButton)
        acceptDesignButton.setOnClickListener {
            onDesignAccepted();
        }

        imageUri = Uri.parse(intent.getStringExtra(INTENT_IMAGE_URI))
        requireNotNull(imageUri) { "no imageUri provided in Intent extras" }

        layoutContainer = findViewById(R.id.layoutContainer)

        val inputStream = contentResolver.openInputStream(imageUri)
        val svg = SVG.getFromInputStream(inputStream)

        imageView = SVGImageView(this)
        imageView!!.setSVG(svg)
        imageView!!.layoutParams = ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT)

        layoutContainer!!.addView(imageView)

        detector = ScaleGestureDetector(this, ScaleListener())


        // Check if permission is already granted
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) {
            // Give first an explanation, if needed.
            if (ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission.CAMERA)) {
                // Show an explanation to the user *asynchronously* -- don't block
                // this thread waiting for the user's response! After the user
                // sees the explanation, try again to request the permission.
            } else {

                // No explanation needed, we can request the permission.
                ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.CAMERA), 1);
            }
        }
    }

    private fun onDesignAccepted() {
        var intent = SessionActivity.newIntent(this, imageUri!!, posX, posY, scale)
        startActivity(intent)
    }

    private fun invalidate() {
        imageView!!.scaleX = scale
        imageView!!.scaleY = scale
    }

    fun onTouch(view: View, event: MotionEvent): Boolean {
        val x = event.rawX.toInt()
        val y = event.rawY.toInt()

        val pointerCount = event.pointerCount

        when (event.action and MotionEvent.ACTION_MASK) {

            MotionEvent.ACTION_DOWN -> {
                val layoutParams = view.layoutParams as RelativeLayout.LayoutParams
                posX = x - layoutParams.leftMargin
                posY = y - layoutParams.topMargin
            }

            MotionEvent.ACTION_MOVE -> {
                if (pointerCount == 1) {
                    val Params = view.layoutParams as RelativeLayout.LayoutParams
                    Params.leftMargin = x - posX
                    Params.topMargin = y - posY
                    Params.rightMargin = -500
                    Params.bottomMargin = -500
                    view.layoutParams = Params
                }

                if (pointerCount == 2) {

                    val layoutParams1 = view.layoutParams as RelativeLayout.LayoutParams
                    layoutParams1.width = posX + event.x.toInt()
                    layoutParams1.height = posY + event.y.toInt()
                    view.layoutParams = layoutParams1
                }

                //Rotation
                if (pointerCount == 3) {
                    //Rotate the ImageView
                    view.setRotation(view.getRotation() + 10.0f)
                }
            }
        }

        // Schedules a repaint for the root Layout.
        layoutContainer!!.invalidate()
        return true
    }

    private inner class ScaleListener : ScaleGestureDetector.SimpleOnScaleGestureListener() {
        internal var onScaleBegin = 0f
        internal var onScaleEnd = 0f

        override fun onScale(detector: ScaleGestureDetector): Boolean {
            scale *= detector.scaleFactor
            scale = Math.max(0.1f, Math.min(scale, 5.0f));
            return true
        }

        override fun onScaleBegin(detector: ScaleGestureDetector): Boolean {
            onScaleBegin = scale

            return true
        }

        override fun onScaleEnd(detector: ScaleGestureDetector) {
            onScaleEnd = scale

            super.onScaleEnd(detector)
        }
    }
}
