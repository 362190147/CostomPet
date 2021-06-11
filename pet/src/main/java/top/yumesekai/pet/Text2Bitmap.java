package top.yumesekai.pet;

import android.app.NativeActivity;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Typeface;

public class Text2Bitmap
{
  private static final int m_SizeKind_HEIGHT = 1;
  private static final int m_SizeKind_WIDTH = 0;
  private static final Paint.Style m_fillpaint;
  private static final int m_fontcolor = -1;
  private static final String m_fontpath = "kyuchan.ttf";
  private static final Paint m_paint;
  private static final Bitmap.Config m_pixelformat;
  private static final String m_sdfontpath ="/sdcard/Android/data/local.mediav.testdrawfigure/files/kyuchan.ttf";
  private static final Paint.Style m_shadowpaint;
  private static Typeface m_typeface = Typeface.SANS_SERIF;
  private static final boolean m_useAntiAliasing = true;

  static
  {
    m_fillpaint		= Paint.Style.FILL;
    m_shadowpaint	= Paint.Style.STROKE;
    m_pixelformat	= Bitmap.Config.ALPHA_8;
    m_paint = new Paint();
  }

  private static final Bitmap doGetBitmap(String text, int textSize, int maxWidth, int strokeWidth, NativeActivity nativeActivity)
  {
    fontSetup(textSize, strokeWidth, nativeActivity);
    String str = text.substring(0, m_paint.breakText(text, true, maxWidth, null));
    int i = measureTextWidth(str);
    int j = measureTextHeight();
    if ((i == 0) || (j == 0))
      return null;
    Bitmap localBitmap = Bitmap.createBitmap(i + strokeWidth * 2, j, m_pixelformat);
    new Canvas(localBitmap).drawText(str, strokeWidth, textSize - m_SizeKind_HEIGHT, m_paint);
    return localBitmap;
  }

  private static final void fontSetup(int textSize, int StrokeWidth, NativeActivity nativeActivity)
  {
    m_paint.setColor(m_fontcolor);
    m_paint.setTextSize(textSize);
    m_paint.setAntiAlias(m_useAntiAliasing);
    loadFont(nativeActivity);
    m_paint.setTypeface(m_typeface);
    m_paint.setSubpixelText(true);
    if (StrokeWidth > 0)
    {
      m_paint.setStrokeWidth(StrokeWidth);
      m_paint.setStyle(m_shadowpaint);
      return;
    }
    m_paint.setStyle(m_fillpaint);
  }

  static final Bitmap getBitmap(String text, int textSize, int paramInt2)
  {
    return getBitmap(text, textSize, paramInt2, null);
  }

  static final Bitmap getBitmap(String text, int textSize, int maxWidth, NativeActivity nativeActivity)
  {
    return doGetBitmap(text, textSize, maxWidth, m_SizeKind_WIDTH , nativeActivity);
  }

  static final Bitmap getShadowBitmap(String text, int textSize, int paramInt2, int paramInt3)
  {
    return getShadowBitmap(text, textSize, paramInt2, paramInt3, null);
  }

  static final Bitmap getShadowBitmap(String text, int textSize, int paramInt2, int paramInt3, NativeActivity nativeActivity)
  {
    return doGetBitmap(text, textSize, paramInt2, paramInt3, nativeActivity);
  }

  static final int getTextHeight(String text, int textSize, int paramInt2)
  {
    return getTextHeight(text, textSize, paramInt2, null);
  }

  static final int getTextHeight(String text, int textSize, int paramInt2, NativeActivity nativeActivity)
  {
    return getTextSize(text, textSize, 1, paramInt2, nativeActivity);
  }

  private static final int getTextSize(String text, int textSize, int paramInt2, int strokeWidth, NativeActivity nativeActivity)
  {
    fontSetup(textSize, strokeWidth, nativeActivity);
    if (paramInt2 == 0)
      return measureTextWidth(text) + strokeWidth * 2;
    return measureTextHeight();
  }

  static final int getTextWidth(String text, int textSize, int paramInt2)
  {
    return getTextWidth(text, textSize, paramInt2, null);
  }

  static final int getTextWidth(String text, int textSize, int paramInt2, NativeActivity nativeActivity)
  {
    return getTextSize(text, textSize, 0, paramInt2, nativeActivity);
  }

  private static final void loadFont(NativeActivity nativeActivity)
  {
    if (m_typeface == null)
    {
      if (nativeActivity == null)
        m_typeface = Typeface.createFromFile(m_sdfontpath);
    }
    else
      return;
    m_typeface = Typeface.createFromAsset(nativeActivity.getAssets(), m_fontpath);
  }

  private static final int measureTextHeight()
  {
    Paint.FontMetrics localFontMetrics = m_paint.getFontMetrics();
    return (int)(0.5F + (Math.abs(localFontMetrics.top) + Math.abs(localFontMetrics.bottom)));
  }

  private static final int measureTextWidth(String text)
  {
    return (int)(0.5F + m_paint.measureText(text));
  }
}