package com.nuri.dtlsproxy.util;

public class ProxyUtil {

    public static String byteArrayToHexString(byte[] paramArrayOfByte)
    {
      StringBuilder localStringBuilder = new StringBuilder();
      for (int i = 0; i < paramArrayOfByte.length; i++)
      {
        String str = Integer.toHexString(0xFF & paramArrayOfByte[i]);
        if (str.length() == 1) {
          localStringBuilder.append('0');
        }
        localStringBuilder.append(str);
      }
      return localStringBuilder.toString();
    }
}
