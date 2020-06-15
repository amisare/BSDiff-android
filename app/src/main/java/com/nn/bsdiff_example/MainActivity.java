package com.nn.bsdiff_example;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.os.Bundle;
import android.util.Log;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.security.MessageDigest;

import com.nn.bsdiff.BSDiff;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        File oldFile = getAssetsCacheFile(this, "bsdiff_old.txt");
        File newFile = getAssetsCacheFile(this, "bsdiff_new.txt");
        File patchFile = getAssetsCacheFile(this, "bsdiff_patch.patch");

        String newFileMD5 = getFileMD5(newFile);
        String patchFileMD5 = getFileMD5(patchFile);

        File genPatchFile = new File(this.getCacheDir(), "gen_bsdiff_patch.patch");
        File genNewFile = new File(this.getCacheDir(), "gen_bsdiff_new.txt");


        int i = BSDiff.diff(oldFile.getPath(), newFile.getPath(), genPatchFile.getPath());
        Log.v("diff", "ret：" + String.valueOf(i));
        String genPatchFileMD5 = getFileMD5(genPatchFile);
        if (genPatchFileMD5.equals(patchFileMD5)) {
            Log.v("diff", "diff sucess");
        } else {
            Log.v("diff", "diff fail");
        }

        int j = BSDiff.patch(oldFile.getPath(), genNewFile.getPath(), patchFile.getPath());
        Log.v("patch", "ret：" + String.valueOf(j));
        String genNewFileMD5 = getFileMD5(genNewFile);
        if (genNewFileMD5.equals(newFileMD5)) {
            Log.v("patch", "patch sucess");
        } else {
            Log.v("patch", "patch fail");
        }
    }

    public File getAssetsCacheFile(Context context, String fileName) {
        File cacheFile = new File(context.getCacheDir(), fileName);
        try {
            InputStream inputStream = context.getAssets().open(fileName);
            try {
                FileOutputStream outputStream = new FileOutputStream(cacheFile);
                try {
                    byte[] buf = new byte[1024];
                    int len;
                    while ((len = inputStream.read(buf)) > 0) {
                        outputStream.write(buf, 0, len);
                    }
                } finally {
                    outputStream.close();
                }
            } finally {
                inputStream.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return cacheFile;
    }

    public static String getFileMD5(File file) {
        if (!file.isFile()) {
            return null;
        }
        MessageDigest digest = null;
        FileInputStream in = null;
        byte buffer[] = new byte[1024];
        int len;
        try {
            digest = MessageDigest.getInstance("MD5");
            in = new FileInputStream(file);
            while ((len = in.read(buffer, 0, 1024)) != -1) {
                digest.update(buffer, 0, len);
            }
            in.close();
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
        return bytesToHexString(digest.digest());
    }

    public static String bytesToHexString(byte[] src) {
        StringBuilder stringBuilder = new StringBuilder("");
        if (src == null || src.length <= 0) {
            return null;
        }
        for (int i = 0; i < src.length; i++) {
            int v = src[i] & 0xFF;
            String hv = Integer.toHexString(v);
            if (hv.length() < 2) {
                stringBuilder.append(0);
            }
            stringBuilder.append(hv);
        }
        return stringBuilder.toString();
    }
}
