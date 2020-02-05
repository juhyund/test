package com.aimir.util;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.math.BigInteger;
import java.net.InetAddress;
import java.text.DecimalFormat;
import java.util.Calendar;
import java.util.LinkedList;

import org.apache.mina.core.buffer.IoBuffer;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.nuri.emi.fep.config.Constants;
import com.nuri.emi.fep.util.Bcd;

public class DataUtil
{
	static Logger logger = LoggerFactory.getLogger(DataUtil.class);
	
    /**
     * constructor
     */
    public DataUtil()
    {
    }
  
    /**
     * encode MCU ID
     *
     * @param mcuId <code>String</code> MCU ID
     * @return bytes <code>byte[]</code>
     */
    public static byte[] encodeMcuId(String mcuId)
    {
        return mcuId.getBytes();
    }

    /**
     * decode MCU ID
     *
     * @param mcuId <code>byte[]</code> MCU ID
     * @return mcuId <code>String</code>
     */
    public static String decodeMcuId(byte[] mcuId)
    {
        return new String(mcuId);
    }

    /**
     * get FEP ID Bytes
     *
     * @return bytes <code>byte[]</code>
     */
    public static byte[] getFepIdBytes()
    {
        String fepId="127.0.0.1";
        try {
            InetAddress ia = InetAddress.getLocalHost();
            fepId = ia.getHostAddress();
        }catch(Exception ex) { }
        return encodeIpAddr(fepId);
    }

    /**
     * get FEP ID String
     *
     * @return fepId <code>String</code>
     */
    private static String serverIpAddress = null;
    public static String getFepIdString()
    {
        if(serverIpAddress == null)
        {
            String fepId="127.0.0.1";
            try {
                InetAddress ia = InetAddress.getLocalHost();
                fepId = ia.getHostAddress();
            }catch(Exception ex) { }
            serverIpAddress = fepId;
        }
        return serverIpAddress;
    }

    /**
     * encode IP address
     *
     * @param fepId <code>String</code>
     * @return bytes <code>byte[]</code>
     */
    public static byte[] encodeIpAddr( String fepId)
    {
        String[] ips = fepId.split("[\\.]");
        byte[] res = new byte[ips.length];
        for(int i = 0 ; i < ips.length ; i++)
        {
            res[i] = getByteToInt(ips[i]);
        }

        return res;
    }

    /**
     * decode IP address
     *
     * @param fepId <code>byte[]</code>
     * @return fepId <code>String</code>
     */
    public static String decodeIpAddr(byte[] fepId )
    {
        StringBuffer sb = new StringBuffer();
        sb.append(getIntToByte(fepId[0]));
        for(int i = 1 ; i < fepId.length ; i++)
        {
            sb.append('.').append(getIntToByte(fepId[i]));
        }
        return sb.toString();
    }
    
    /**
     * decode IPv6 address
     *
     * @param fepId <code>byte[]</code>
     * @return fepId <code>String</code>
     */
    public static String decodeIPv6Addr(byte[] fepId )
    {
        StringBuffer sb = new StringBuffer();
        sb.append(getIntToByte(fepId[0]));
        for(int i = 1 ; i < fepId.length ; i++)
        {
            sb.append(':').append(getIntToByte(fepId[i]));
        }
        return sb.toString();
    }
    
    /**
     * decode IPv6 address
     *
     * @param fepId <code>byte[]</code>
     * @return fepId <code>String</code>
     */
    public static String decodeIPv6Addr2(byte[] fepId)
    {
    	String ipv6 = Hex.decode(fepId);
        StringBuffer sb = new StringBuffer();
        sb.append(ipv6.substring(0,4)+":");
        sb.append(ipv6.substring(4,8)+":");
        sb.append(ipv6.substring(8,12)+":");
        sb.append(ipv6.substring(12,16)+":");
        sb.append(ipv6.substring(16,20)+":");
        sb.append(ipv6.substring(20,24)+":");
        sb.append(ipv6.substring(24,28)+":");
        sb.append(ipv6.substring(28,32));
        return sb.toString();
    }

    /**
     * decode IP address
     *
     * @param fepId <code>byte[]</code>
     * @return fepId <code>String</code>
     */
    public static String decodeGMT(byte[] gmtTime )
    {
        StringBuffer sb = new StringBuffer();
        byte[] gmt = new byte[2];
        byte[] dst = new byte[2];
        byte[] datetime = new byte[7];
        System.arraycopy(gmtTime,0,gmt,0,2);
        System.arraycopy(gmtTime,2,dst,0,2);
        System.arraycopy(gmtTime,4,datetime,0,7);
        sb.append("GMT").append(getIntTo2Byte(gmt)).append(',');
        sb.append("DST").append(getIntTo2Byte(dst)).append(',');
        sb.append(Bcd.decodeTime(datetime));

        return sb.toString();
    }

    /**
     * encode GMT
     *
     * @param GMT <code>String</code>
     * @return bytes <code>byte[]</code>
     */
    public static byte[] encodeGMT(String gmtTime)
    {
        String[] ips = gmtTime.split("[\\,]");
        byte[] res = new byte[11];
        int GMT = 0, DST = 0;
        if(ips[0].substring(3,4).equals("-")){
            GMT = Integer.parseInt(ips[0].substring(4))*(-1);
        }else{
            GMT = Integer.parseInt(ips[0].substring(3));
        }
        if(ips[1].substring(3,4).equals("-")){
            DST = Integer.parseInt(ips[1].substring(4))*(-1);
        }else{
            DST = Integer.parseInt(ips[1].substring(3));
        }

        byte[] gmt = get2ByteToInt(GMT);
        byte[] dst = get2ByteToInt(DST);
        byte[] datetime = Bcd.encodeTime(ips[2]);
        System.arraycopy(gmt,0,res,0,2);
        System.arraycopy(dst,0,res,2,2);
        System.arraycopy(datetime,0,res,4,7);
        return res;
    }

    // bit operation method

    /**
     * convert int to byte
     *
     * @param val <code>String</code>
     * @return byte <code>byte</code>
     */
    public static byte getByteToInt(String val)
    {
        int ival = Integer.parseInt(val);
        return (byte)ival;
    }

    /**
     * convert int to byte
     *
     * @param val <code>int</code>
     * @return byte <code>byte</code>
     */
    public static byte getByteToInt(int val)
    {
        return (byte)val;
    }

    /**
     * convert byte to int
     *
     * @param val <code>byte</code>
     * @return int <code>int</code>
     */
    public static int getIntToByte(byte val)
    {
        int ival = ((val & 0xff) << 0);
        return ival;
    }

    /**
     * convert char to 2 bytes
     * @param val <code>val</code>
     * @return bytes <code>byte[]</code>
     */
    public static byte[] get2ByteToChar(char val){
    	byte[] twoByte = new byte[2];
    	twoByte[0] = (byte)(val >> 8);
    	twoByte[1] = (byte)(val);
    	return twoByte;
    }
    
    /**
     * convert int to 2 bytes
     *
     * @param val <code>val</code>
     * @return bytes <code>byte[]</code>
     */
    public static byte[] get2ByteToInt(String val)
    {
        int ival = 0;
        try { ival = Integer.parseInt(val); }
        catch(Exception ex) {}

        byte[] res = new byte[2];
        res[0] = (byte)(ival >> 8);
        res[1] = (byte)ival;
        return res;
    }

    /**
     * convert int to 2 bytes
     *
     * @param val <code>int</code>
     * @return bytes <code>byte[]</code>
     */
    public static byte[] get2ByteToInt(int val)
    {
        byte[] res = new byte[2];
        res[0] = (byte)(val >> 8);
        res[1] = (byte)val;
        return res;
    }

    public static byte[] get2ByteToInt(boolean isConvert, int val)
    {
        byte[] res = new byte[2];
        res[0] = (byte)(val >> 8);
        res[1] = (byte)val;
        convertEndian(isConvert, res);
        return res;
    }

    /**
     * convert 2 bytes to int
     *
     * @param val <code>byte[]</code>
     * @return int <code>int</code>
     */
    public static int getIntTo2Byte(byte[] val)
    {
        int res = ((val[0] & 0xff) << 8)
            + (val[1] & 0xff);
        return res;
    }
    /**
     * convert 2 bytes to int
     *
     * @param val1 <code>byte</code>
     * @param val2 <code>byte</code>
     * @return int <code>int</code>
     */
    public static int getIntTo2Byte(byte val1, byte val2)
    {
        int res = ((val1 & 0xff) << 8)
            + (val2 & 0xff);
        return res;
    }

    /**
     * convert int to 3 bytes
     *
     * @param val <code>int</code>
     * @return bytes <code>byte[]</code>
     */
    public static byte[] get3ByteToInt(int val)
    {
        byte[] res = new byte[3];
        res[0] = (byte)(val >> 16);
        res[1] = (byte)(val >> 8);
        res[2] = (byte)val;
        return res;
    }

    /**
     * convert int to 4 bytes
     *
     * @param val <code>int</code>
     * @return bytes <code>byte[]</code>
     */
    public static byte[] get4ByteToInt(int val)
    {
        byte[] res = new byte[4];
        res[0] = (byte)(val >> 24);
        res[1] = (byte)(val >> 16);
        res[2] = (byte)(val >> 8);
        res[3] = (byte)val;
        return res;
    }
    
    /**
     * convert long to 6 bytes
     *
     * @param val <code>long</code>
     * @return bytes <code>byte[]</code>
     */
    public static byte[] get6ByteToInt(long val)
    {
        byte[] res = new byte[6];
        res[0] = (byte)(val >> 40);
        res[1] = (byte)(val >> 32);
        res[2] = (byte)(val >> 24);
        res[3] = (byte)(val >> 16);
        res[4] = (byte)(val >> 8);
        res[5] = (byte)val;
        return res;
    }
    
    /**
     * convert long to 8 bytes
     *
     * @param val <code>long</code>
     * @return bytes <code>byte[]</code>
     */
    public static byte[] get8ByteToInt(long val)
    {
        byte[] res = new byte[8];
        res[0] = (byte)(val >> 56);
        res[1] = (byte)(val >> 48);
        res[2] = (byte)(val >> 40);
        res[3] = (byte)(val >> 32);
        res[4] = (byte)(val >> 24);
        res[5] = (byte)(val >> 16);
        res[6] = (byte)(val >> 8);
        res[7] = (byte)val;
        return res;
    }

    public static byte[] getPLCPortByte(boolean isConvert, int port) {
    	byte[] res=get4ByteToInt(port);
    	convertEndian(isConvert, res);
    	return res;
    }


    /**
     * convert int to 2 bytes
     *
     * @param val <code>int</code>
     * @return bytes <code>byte[]</code>
     */
    public static byte[] get4ByteToInt(long val)
    {
        byte[] res = new byte[4];
        res[0] = (byte)(val >> 24);
        res[1] = (byte)(val >> 16);
        res[2] = (byte)(val >> 8);
        res[3] = (byte)val;
        return res;
    }

    

    /**
     * convert 3 bytes to int
     *
     * @param val <code>byte[]</code>
     * @return int <code>int</code>
     */
    public static int getIntTo3Byte(byte[] val)
    {
        int res = ((val[0] & 0xff) << 16)
            + ((val[1] & 0xff) << 8)
            + (val[2] & 0xff);
        return res;
    }
    
    /**
     * convert 4 bytes to int
     *
     * @param val <code>byte[]</code>
     * @return int <code>int</code>
     */
    public static int getIntTo4Byte(byte[] val)
    {
        int res = ((val[0] & 0xff) << 24)
            + ((val[1] & 0xff) << 16)
            + ((val[2] & 0xff) << 8)
            + (val[3] & 0xff);
        return res;
    }
    
    /**
     * convert 6 bytes to long
     *
     * @param val <code>byte[]</code>
     * @return long <code>long</code>
     */
    public static long getLongTo6Byte(byte[] val)
    {
    	long res = ((val[0] & 0xFFL) << 40)
        		+ ((val[1] & 0xFFL) << 32)
        		+ ((val[2] & 0xFFL) << 24)
        		+ ((val[3] & 0xFFL) << 16)
                + ((val[4] & 0xFFL) << 8)
                + (val[5] & 0xFFL);
            return res;
    }
    
    /**
     * convert 8 bytes to long
     *
     * @param val <code>byte[]</code>
     * @return long <code>long</code>
     */
    public static long getLongTo8Byte(byte[] val)
    {
    	long res = ((val[0] & 0xFFL) << 56)
    			+ ((val[1] & 0xFFL) << 48)
    			+ ((val[2] & 0xFFL) << 40)
        		+ ((val[3] & 0xFFL) << 32)
        		+ ((val[4] & 0xFFL) << 24)
        		+ ((val[5] & 0xFFL) << 16)
                + ((val[6] & 0xFFL) << 8)
                + (val[7] & 0xFFL);
            return res;
    }
    
    public static int getIntToBytes(byte[] data)
    {
        int res = 0;
        for(int i = 0 ; i < data.length ; i++)
        {
            if(i > 0) {
				res<<=8;
			}
            res|=(data[i]&0xff);
        }
        return res;
    }

    public static long getLongToBytes(byte[] data)
    {
        long res = 0;
        for(int i = 0 ; i < data.length ; i++)
        {
            if(i > 0) {
				res<<=8;
			}
            res|=(data[i]&0xff);
        }
        return res;
    }


    /**
     * getBCDtoBytes (Ex: 0x00045612 -> 45612)
     *
     * @param data
     * @return
     */
    public static String getBCDtoBytes(byte[] data){
		String bcd="";
		boolean first=true;
		for(int i=0;i<data.length;i++){
			if(bcd.length()==0&&Integer.parseInt((((data[i]&0xF0)>>4)+(data[i]&0x0F))+"")!=0){
				bcd+=((first&&((data[i]&0xF0)>>4)==0) ? "":((data[i]&0xF0)>>4)+"")+(data[i]&0x0F);
				first=false;
			}else if (!first){
				bcd+=((data[i]&0xF0)>>4)+""+(data[i]&0x0F);
			}
		}
		if(first){
			bcd="0";
		}
		return bcd;
	}


	/**
	 * Get Type G Date For MBus
	 * @param rawData
	 * @return
	 */
	public static Double getDateTo2Byte(byte[] rawData){
    	int day=getIntTo2Byte(rawData)&0x0f;
    	int month=(getIntTo2Byte(rawData)&0xf00)>>8;
    	int year=((getIntTo2Byte(rawData)&0xf000)>>9)|((getIntTo2Byte(rawData)&0xe0)>>5);
    	String yyyymmdd="20"+(year<10?"0"+year:year)+(month<10?"0"+month:month)+(day<10?"0"+day:day);
    	Double doubleYyyymmdd=Double.parseDouble(yyyymmdd);
    	return doubleYyyymmdd;
    }

    /**
     * 4 Bytes -> Date (LSB)
     * Typedef struct
     * {
     * unsigned long sec:6;
     * unsigned long min:6;
     * unsigned long hour:5;
     * unsigned long day:5;
     * unsigned long month:4;
     * unsigned long year:6;
     * } DATE
     * 0x121529B
     * 000100 1000 01010 10000 001010 011011
     *      4    8    10    16     10     27
     * 2004/08/10 16:10:27
     * @param data
     * @return
     */
    public static String convert4ByteToDateString(byte[] data){
        BigInteger b = new BigInteger(data);
        String temp = b.toString(2);
        DecimalFormat df = new DecimalFormat("00");
        StringBuffer sbTemp = new StringBuffer();
        int diff = 32 - temp.length();
        sbTemp.append(2000+Integer.parseInt(temp.substring(0,6-diff),2));
        sbTemp.append(df.format(Integer.parseInt(temp.substring(6-diff,10-diff),2)));
        sbTemp.append(df.format(Integer.parseInt(temp.substring(10-diff,15-diff),2)));
        sbTemp.append(df.format(Integer.parseInt(temp.substring(15-diff,20-diff),2)));
        sbTemp.append(df.format(Integer.parseInt(temp.substring(20-diff,26-diff),2)));
        sbTemp.append(df.format(Integer.parseInt(temp.substring(26-diff,32-diff),2)));

        return sbTemp.toString();
    }

    public static void arraycopy(IoBuffer src,int spos,byte[] dest,
            int dpos,int dlen)
    {
        for(int i = dpos ; i < dlen ; i++) {
			dest[i]=src.get(spos++);
		}
    }
    
	// 0x00인 바이트 제거
	public static byte[] trim0x00Byte(byte[] src){
		byte[] result = null;
		
		if(0 < src.length){
			LinkedList<Byte> list = new LinkedList<Byte>();
			for(byte b : src){
				if(b != 0x00){
					list.add(b);
				}
			}	

		    result = new byte[list.size()];
			for(int i=0; i<list.size(); i++){
				result[i] = (byte) list.get(i);
			}				
		}
		return result;
	}

    public static byte getVersionByte(String ver)
    {
        int idx = ver.indexOf(".");
        int pre = Integer.parseInt(ver.substring(0,idx));
        int post = Integer.parseInt(ver.substring(idx+1,
                    ver.length()));
        int f = (pre << 4) | post;
        return (byte)(f & 0xff);
    }

    public static String getVersionString(byte ver)
    {
        int pre = (ver & 0xf0) >> 4;
        int post = (ver & 0x0f);

        return pre+"."+post;
    }
    
    public static String getVersionString(int ver)
    {
    	byte[] verBytes = get2ByteToInt(ver);
        int pre = verBytes[0] & 0xFF;
        int post = verBytes[1] & 0xFF;

        return pre+"."+post;
    }

    /**
     * merge to byte array
     *
     * @param src1 <code>byte[]</code>
     * @param off1 <code>int</code>
     * @param len1 <code>int</code>
     * @param src2 <code>byte[]</code>
     * @param off2 <code>int</code>
     * @param len2 <code>int</code>
     * @return bytes <code>byte[]</code>
     */
    public static byte[] arrayAppend(byte[] src1,int off1,
            int len1, byte[] src2, int off2, int len2)
    {
        byte[] dest = new byte[len1 + len2];
        System.arraycopy(src1,off1,dest,0,len1);
        System.arraycopy(src2,off2,dest,len1,len2);
        return dest;
    }

    /**
     * merge to byte array
     *
     * @param buf1 <code>byte[]</code>
     * @param buf2 <code>byte[]</code>
     * @return bytes <code>byte[]</code>
     */
    public static byte[] append(byte[] buf1, byte[] buf2)
    {
        byte[] newbuf = new byte[buf1.length + buf2.length];
        System.arraycopy(buf1,0,newbuf,0,buf1.length);
        System.arraycopy(buf2,0,newbuf,buf1.length,buf2.length);
        return newbuf;
    }

    /**
     * get OID String
     *
     * @param oid <code>byte[]</code>
     * @return oid <code>String</code>
     */
    public static String getOIDString(byte[] oid)
    {
        StringBuffer sb = new StringBuffer();
        sb.append(getIntToByte(oid[0]));
        sb.append('.');
        sb.append(getIntToByte(oid[1]));
        sb.append('.');
        sb.append(getIntToByte(oid[2]));
        return sb.toString();
    }


  


    public static boolean isSubOidByOid(String poid,String coid)
    {
        try
        {
            int idx = poid.indexOf(".0");
            String prefix = null;
            if(idx > 0)
            {
                prefix = poid.substring(0,idx+1);
            } else
            {
                prefix = poid;
            }
            return coid.startsWith(prefix);
        }
        catch(Exception ex)
        {
        	logger.error("isSubMIBByOid failed :",ex);
        }
        return false;
    }

    /**
     * convert endian
     * @param stream <code>byte[]</code> byte stream
     */
    public static void convertEndian(byte[] stream)
    {
        byte b = 0;
        if(Constants.LITTLE_ENDIAN)
        {
            int j = stream.length/2;
            int len = stream.length - 1;
            for(int i = 0 ; i < j ; i++)
            {
                b = stream[i];
                stream[i] = stream[len - i];
                stream[len - i] = b;
            }
        }
    }

    /**
     * convert endian
     * @param isConvert
     * @param stream
     */
    public static void convertEndian(boolean isConvert, byte[] stream){
    	if(isConvert){
    		convertEndian(stream);
    	}
    }

    /**
     * convert endian
     * @param stream <code>byte[]</code> byte stream
     */
    public static void reverse(byte[] stream)
    {
        byte b = 0;
        int j = stream.length/2;
        int len = stream.length - 1;
        for(int i = 0 ; i < j ; i++)
        {
            b = stream[i];
            stream[i] = stream[len - i];
            stream[len - i] = b;
        }
    }

    /**
     * convert endian
     * @param stream <code>byte[]</code> byte stream
     */
    public static byte[] getReverseBytes(byte[] stream)
    {
        byte[] bx = new byte[stream.length];
        System.arraycopy(stream,0,bx,0,bx.length);
        reverse(bx);
        return bx;
    }

    /**
     * convert endian
     * @param stream <code>byte[]</code> byte stream
     */
    public static void reverse(byte[] stream,int pos,int len)
    {
        byte b = 0;
        int j = len/2;
        int length = len - 1;
        for(int i = pos ; i < pos+j ; i++)
        {
            b = stream[i+pos];
            stream[i+pos] = stream[(pos+length) - i];
            stream[(pos+length) - (i+pos)] = b;
        }
    }

    public static byte[] select(byte[] b, int offset, int len)
     throws Exception
    {
        if(b == null || offset < 0 || offset > b.length ||
                len < 1 || b.length < len) {
			throw new Exception("Wrong Parameter Input");
		}

        byte[] des = new byte[len];

        System.arraycopy(b,offset,des,0,len);
        return des;
    }

    public static String convType(String type)
    {
        String convType = null;

        if (type == null)
        {
            return null;
        }

        if (type.equals("string")) {
			convType = "OCTET";
		}
		else if (type.equals("char")) {
			convType = "OCTET";
		}
		else if (type.equals("int")) {
			convType = "INT";
		}
		else if (type.equals("short")) {
			convType = "SHORT";
		}
		else if (type.equals("STREAM")) {
			convType = "OCTET";
		}
		else if (type.equals("STRING")) {
			convType = "OCTET";
		}
		else {
			convType = type;
		}

        return convType;
    }

    private static byte[] readByteFromFile(File file)
        throws Exception
    {
        InputStream is = new FileInputStream(file);
        try {
            ByteArrayOutputStream baos =
                new ByteArrayOutputStream((int) file.length());
            // initial size
            byte[] buffer = new byte[128];
            int bytesRead = is.read(buffer, 0, buffer.length);
            while (bytesRead > 0) {
                baos.write(buffer, 0, bytesRead);
                bytesRead = is.read(buffer, 0, buffer.length);
            }
            return baos.toByteArray();
        } finally
        {
            if (is != null)
            {
                is.close();
            }
        }
    }

    public static byte[] setFloat(float v) throws Exception {
        return setInt(Float.floatToIntBits(v));
    }

    public static byte[] setInt(int v) throws Exception {

        byte[] b = new byte[4];
        b[0] = (byte) ((v >>> 24) & 0xFF);
        b[1] = (byte) ((v >>> 16) & 0xFF);
        b[2] = (byte) ((v >>>  8) & 0xFF);
        b[3] = (byte) ((v >>>  0) & 0xFF);
        return b;
    }

    public static float getFloat(byte[] b,int offset)
                    throws Exception {
        return Float.intBitsToFloat(getInt(b,offset));
    }

    public static int getInt(byte[] buf, int offset)
                throws Exception {

        int ch1 = buf[offset++]&0xFF;
        int ch2 = buf[offset++]&0xFF;
        int ch3 = buf[offset++]&0xFF;
        int ch4 = buf[offset++]&0xFF;
        if ((ch1 | ch2 | ch3 | ch4) < 0) {
			throw new Exception("NULL");
		}
        return ((ch1 << 24) + (ch2 << 16) + (ch3 << 8) + (ch4 << 0));
    }

    /**
     * @param pos
     * @param rawData
     * @param data
     * @return
     */
    public static int copyBytes(boolean isConvert, int pos, byte[] rawData, byte[] data) {
		System.arraycopy(rawData, pos, data, 0, data.length);
		convertEndian(isConvert, data);
		return pos+=data.length;
	}

    /**
     * @param data
     * @return
     */
    public static String getString(byte[] data)
    {
        return new String(data);
    }

    /**
     * byte배열의 startPosition으로부터 cutArrayLenth길이만큼 가져온다.
     * @param data
     * @param startPosition
     * @param cutArrayLenth
     * @return
     */
    public static byte[] getByteArrayByLenth(byte[] data, int startPosition, int cutArrayLenth)
    {
    	if(data.length < (startPosition + cutArrayLenth -1)){
    		return null;
    	}else{
            byte[] temp = new byte[cutArrayLenth];
            System.arraycopy(data, startPosition, temp, 0, cutArrayLenth);
            return temp;
    	}
    }

    
    
    
    /**
     * @param data
     * @return yyyyMMddhhmmss
     * @throws Exception
     */
    public static String getPLCDate(byte[] data) throws Exception {
    	String yyyy="";
    	String MM="";
    	String dd="";
    	String hh="";
    	String mm="";
    	String ss="";
    	if(data.length!=7) {
    		throw new Exception("PLC TIME LENGTH IS INVALID!");
    	}else {
    		yyyy="20"+((data[0]&0xF0)>>4)+""+(data[0]&0x0F);
    		MM=((data[1]&0xF0)>>4)+""+(data[1]&0x0F);
    		dd=((data[2]&0xF0)>>4)+""+(data[2]&0x0F);
    		hh=((data[4]&0xF0)>>4)+""+(data[4]&0x0F);
    		mm=((data[5]&0xF0)>>4)+""+(data[5]&0x0F);
    		ss=((data[6]&0xF0)>>4)+""+(data[6]&0x0F);
    	}
    	return yyyy+MM+dd+hh+mm+ss;
    }
    
    /**
     * 
     * @param 7byte
     * @return yyyyMMddhhmmss
     * @throws Exception
     */
    public static String getEMnvModemDate(byte[] data) throws Exception {
    	String yyyy="";
    	String MM="";
    	String dd="";
    	String hh="";
    	String mm="";
    	String ss="";
    	if(data.length!=7) {
    		throw new Exception("Modem date's length is invalid.");
    	}else {
    		yyyy = String.valueOf(getIntTo2Byte(getByteArrayByLenth(data, 0, 2)));
    		MM = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 2, 1)[0]));
    		dd = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 3, 1)[0]));
    		hh = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 4, 1)[0]));
    		mm = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 5, 1)[0]));
    		ss = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 6, 1)[0]));
    	}
    	return yyyy+MM+dd+hh+mm+ss;
    }
    
    /**
     * 
     * @param 6byte
     * @return yyyyMMddhhmm
     * @throws Exception
     */
    public static String getEMnvDate6Byte(byte[] data) throws Exception {
    	String yyyy="";
    	String MM="";
    	String dd="";
    	String hh="";
    	String mm="";
    	if(data.length!=6) {
    		throw new Exception("Date's length is invalid.");
    	}else {
    		yyyy = String.valueOf(getIntTo2Byte(getByteArrayByLenth(data, 0, 2)));
    		MM = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 2, 1)[0]));
    		dd = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 3, 1)[0]));
    		hh = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 4, 1)[0]));
    		mm = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 5, 1)[0]));    		
    	}
    	return yyyy + MM + dd + hh + mm;
    }    
    
    public static String getDateTimeByDLMS_OCTETSTRING_Length(byte[] data){
    	String dateTime = "";
    	try {
    		if(data.length == 4){
    			dateTime = getTimeByDLMS_OCTETSTRING4(data);
    		}else if(data.length == 5){
    			dateTime = getDateByDLMS_OCTETSTRING5(data);
    		}else if(data.length == 12){
    			dateTime = getDateTimeByDLMS_OCTETSTRING12(data);
    		}else {
    			dateTime = "UNKNOWN_TIME";
    		}
		} catch (Exception e) {
			dateTime = "UNKNOWN_TIME";
		}
		return dateTime;
    }
    
    public static String getDateTimeByDLMS_OCTETSTRING12(byte[] data) throws Exception {
    	//String yearHighByte = "";
    	//String yearLowByte = "";
    	
    	String yyyy="";
    	String month="";
    	String dayOfMonth="";
    	String dayOfWeek="";            // Skip.
    	String hour="";
    	String minute="";
    	String second="";
    	String hundredthsOfSecond="";   // Skip.
    	String deviationHighbyte = "";  // Skip.
    	String deviationLowbyte = "";   // Skip.
    	String clockStatus = "";        // Skip.
    	

    	if(data.length != 12) {
    		throw new Exception("OCTET String DateTime's length is invalid.");
    	}else {
//    		yearHighByte = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 0, 1)[0]));
//    		yearHighByte = (yearHighByte.equals("255")) ? "00" : yearHighByte;
//    		
//    		yearLowByte = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 1, 1)[0]));
//    		yearLowByte = (yearLowByte.equals("255")) ? "00" : yearLowByte;
    		
    		yyyy = String.valueOf(getIntTo2Byte(getByteArrayByLenth(data, 0, 2)));
    		yyyy = (yyyy.equals("65535")) ? "00" : yyyy;
    		
    		month = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 2, 1)[0]));
    		month = (month.equals("255")) ? "00" : month;
    		
    		dayOfMonth = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 3, 1)[0]));
    		dayOfMonth = (dayOfMonth.equals("255")) ? "00" : dayOfMonth;
    		
    		//dayOfWeek = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 4, 1)[0]));
    		hour = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 5, 1)[0]));
    		hour = (hour.equals("255")) ? "00" : hour;
    		
    		minute = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 6, 1)[0]));
    		minute = (minute.equals("255")) ? "00" : minute;
    		
    		second = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 7, 1)[0]));
    		second = (second.equals("255")) ? "00" : second;
    		
    		hundredthsOfSecond = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 8, 1)[0]));
    		hundredthsOfSecond = (hundredthsOfSecond.equals("255")) ? "00" : hundredthsOfSecond;
    	}
    	//return yearHighByte + yearLowByte + month + dayOfMonth + hour + minute + second;
    	return yyyy + month + dayOfMonth + hour + minute + second;
    }
    
    
	public static byte[] getDLMS_OCTETSTRING12ByDateTime(Calendar cal) throws Exception {
		/*
		 {
			year highbyte,
			year lowbyte,
			month,
			day of month,
			day of week,
			hour,
			minute,
			second,
			hundredths of second,
			deviation highbyte,
			deviation lowbyte,
			clock status
		 }
		 */
		byte[] dateTime = new byte[] {};
		dateTime = DataUtil.append(dateTime, DataUtil.get2ByteToInt(cal.get(Calendar.YEAR))); // year highbyte, year lowbyte
		dateTime = DataUtil.append(dateTime, new byte[] { DataUtil.getByteToInt(cal.get(Calendar.MONTH) + 1) }); // month
		dateTime = DataUtil.append(dateTime, new byte[] { DataUtil.getByteToInt(cal.get(Calendar.DAY_OF_MONTH)) }); // day of month
		dateTime = DataUtil.append(dateTime, new byte[] { DataUtil.getByteToInt(cal.get(Calendar.DAY_OF_WEEK) - 1) }); // day of week
		dateTime = DataUtil.append(dateTime, new byte[] { DataUtil.getByteToInt(cal.get(Calendar.HOUR_OF_DAY)) }); // hour
		dateTime = DataUtil.append(dateTime, new byte[] { DataUtil.getByteToInt(cal.get(Calendar.MINUTE)) }); // minute
		dateTime = DataUtil.append(dateTime, new byte[] { DataUtil.getByteToInt(cal.get(Calendar.SECOND)) }); // second
		dateTime = DataUtil.append(dateTime, new byte[] { 0x00 }); // hundredths of second
		dateTime = DataUtil.append(dateTime, new byte[] { (byte) 0x80, 0x00 }); // deviation highbyte, deviation lowbyte  => 0x8000 = not specified
		dateTime = DataUtil.append(dateTime, new byte[] { 0x00 }); // clock status

		return dateTime;
	}
    
    public static String getDateByDLMS_OCTETSTRING5(byte[] data) throws Exception {
    	String yearHighByte="";
    	String yearLowByte="";
    	String month="";
    	String dayOfMonth="";
    	String dayOfWeek="";   // Skip.

    	if(data.length!=5) {
    		throw new Exception("OCTET String Date's length is invalid.");
    	}else {
    		yearHighByte = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 0, 1)[0]));
    		yearHighByte = (yearHighByte.equals("255")) ? "00" : yearHighByte;
    		
    		yearLowByte = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 1, 1)[0]));
    		yearLowByte = (yearLowByte.equals("255")) ? "00" : yearLowByte;
    		
    		month = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 2, 1)[0]));
    		month = (month.equals("255")) ? "00" : month;
    		
    		dayOfMonth = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 3, 1)[0]));
    		dayOfMonth = (dayOfMonth.equals("255")) ? "00" : dayOfMonth;
    		
    		dayOfWeek = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 4, 1)[0]));
    		dayOfWeek = (dayOfWeek.equals("255")) ? "00" : dayOfWeek;
    	}
    	return yearHighByte+yearLowByte+month+dayOfMonth;
    }
    
    public static String getTimeByDLMS_OCTETSTRING4(byte[] data) throws Exception {
    	String hour="";
    	String minute="";
    	String second="";
    	String hundredths="";   // Skip.
    	
    	if(data.length!=4) {
    		throw new Exception("OCTET String Time's length is invalid.");
    	}else {
    		hour = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 0, 1)[0]));
    		hour = (hour.equals("255")) ? "0" : hour;
    		
    		minute = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 1, 1)[0]));
    		minute = (minute.equals("255")) ? "0" : minute;
    		
    		second = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 2, 1)[0]));
    		second = (second.equals("255")) ? "0" : second;
    		
    		hundredths = String.format("%02d", getIntToByte(getByteArrayByLenth(data, 3, 1)[0]));
    		hundredths = (hundredths.equals("255")) ? "0" : hundredths;
    	}
    	return hour+minute+second;
    }
  
    public static String getPLCVer(byte[] data){
    	String ver="Unknown";
    	if(data[0]==0x10) {
    		ver="ver1.0";
    	}
    	else if(data[0]==0x11) {
    		ver="ver1.1";
    	}
    	return ver;
    }

    /**
     * @param data
     * @return
     */
    public static String getPLCIp(byte[] data){
    	String fepIp="Unknown";
    	//fepIp = getIntToByte(data[0])+":"+getIntToByte(data[1])+":"+getIntToByte(data[2])+":"+getIntToByte(data[3])+"/"+getIntToByte(data[4])+":"+getIntToByte(data[5]);
    	fepIp = getIntToByte(data[0])+"."+getIntToByte(data[1])+"."+getIntToByte(data[2])+"."+getIntToByte(data[3]);
    	return fepIp;
    }

    public static byte[] getPLCIpByte(String ip) {
    	byte[] byteIp = null;
    	String splitIp[]=ip.split("[./:]");
    	for(int i=0;i<splitIp.length;i++) {
    		if(byteIp==null) {
    			byteIp=(new byte[]{getByteToInt(splitIp[i])});
    		}
    		else{
    			byteIp=append(byteIp, new byte[]{getByteToInt(splitIp[i])});
    		}
    	}
    	return byteIp;
    }

 

    public static String getPLCMacAddr(byte[] data){
    	String fepIp=Hex.decode(data);
    	fepIp = fepIp.substring(0, 2)+":"+fepIp.substring(2, 4)+":"+fepIp.substring(4, 6)+":"+fepIp.substring(6, 8)+":"+fepIp.substring(8, 10)+":"+fepIp.substring(10, 12);
    	return fepIp;
    }

    public static byte[] getPLCMacAddrByte(String macAddr){
    	return Hex.encode(macAddr.replace(":", ""));
    }

    /**
     * Return Fixed Length Byte Array
     * @param obj
     * @param length return length
     * @return
     */
    public static byte[] getFixedLengthByte(Object obj, int length) {
    	byte[] original = null;
    	byte[] appendByte = null;
    	if(obj instanceof String) {
    		original = ((String)obj).getBytes();
    	}
    	else if(obj instanceof byte[]) {
    		original = (byte[])obj;
    	}
    	if(original.length<length) {
			appendByte = new byte[length-original.length];
		}
    	return appendByte!=null ? DataUtil.append(original, appendByte):original;
    }

    public static String getPLCCommandStr(byte command) {
		switch (command) {
			case 'A':
				return "Acknowledge";
			case 'B':
				return "IRM Status Request";
			case 'C':
				return "IRM  Configuration Set";
			case 'D':
				return "Data Request(Metering Data)";
			case 'E':
				return "Data Request(Max Demand Data)";
			case 'F':
				return "Data Request(LP Data)";
			case 'G':
				return "Data Request(PowerOutage)";
			case 'H':
				return "Data Request(Comm. Status)";
			case 'I':
				return "Meter Status Request";
			case 'J':
				return "Data Request(Trans. Data)";
			case 'M':
				return "Trans. Configuration Data Request";
			case 'N':
				return "Trans. Configuration Set";
			case 'a':
				return "Not Acknowledge";
			case 'b':
				return "IRM Status Response / IRM Trap";
			case 'd':
				return "Response(Metering Data)";
			case 'e':
				return "Response(Max Demand Data)";
			case 'f':
				return "Response(LP Data)";
			case 'g':
				return "Response(PowerOutage)";
			case 'h':
				return "Response(Comm. Status)";
			case 'i':
				return "Meter Status Response / Meter Trap";
			case 'j':
				return "Response(Trans. Data)";
			case 'k':
				return "Trap Info.(PLC Comm. Error Trap)";
			case 'l':
				return "Trap Info.(IR Comm. Error Trap)";
			case 'm':
				return "Trans. Configuration Data Response";
			default:
				return "Unknown";
		}
	}

  
    /**
     * @param sValue
     * @return
     */
    public static Integer toInteger(String sValue){
	    Double d = Double.parseDouble(sValue) ;
	    int i = (int)(d * 1);
	    return i;
	}
    
    /**
     * IP Address split : [\\.]
     *  
     * @param ipAddr
     * @return
     */
    public static String encodeIpAddrToStr(byte[] ipAddr) {
    
        StringBuffer sb = new StringBuffer();
        try{
            String[] ips    = (new String(ipAddr)).split("[\\.]");
            
            
            for(int i=0 ; i < ips.length ; i++){
                sb.append(ips[i]);
            }

        }catch(Exception e){
        	logger.error(" Ip Address split Error " + e.getMessage());
        }
        return sb.toString();
    }
    
    /**
     * Mobile Number split : [\\-]
     * @param mbNum
     * @return
     */
    public static String encodeMobileAddrToStr(byte[] mbNum) {
        
        StringBuffer sb = new StringBuffer();
        try{
            String[] mbs = (new String(mbNum)).split("[\\-]");
            
            
            for(int i=0 ; i < mbs.length ; i++){
                sb.append(mbs[i]);
            }
            
        }catch(Exception e){
        	logger.error(" Mobile Number split Error " + e.getMessage());
        }
        return sb.toString();
    }
    
    
    /**
	 * String 을 BCD Type ByteArray로 변환하는 역할을 한다.<br>
	 * 
	 * @param val
	 * @return
	 * @throws IOException
	 */
	public static byte[] getBCD(String val) throws IOException {

		ByteArrayOutputStream bos = new ByteArrayOutputStream();

		for (int i = 0; i < val.length(); i += 2) {
			// String 을 2 size 읽어와 16진수 숫자로 변환한다.
			String hexString = val.substring(i, i + 2);
			int hexNum = Integer.parseInt(hexString, 16);

			// 변환된 수를 ByteArray 에 입력한다.
			bos.write(hexNum);
		}

		bos.close();

		return bos.toByteArray();
	}
	/**
	 * 입력받은 size 만큼 공간을 확보하고 bytes를 복사한다. 나머지 공간은 fillByte로 채운다.
	 * 
	 * @param bytes
	 * @param fillByte
	 * @param size
	 * @return
	 */
	public static byte[] fillCopy(byte[] bytes, byte fillByte, int size) {
		byte[] data = new byte[size];

		if(bytes.length > size)
			System.arraycopy(bytes, 0, data, 0, size);
		else
			System.arraycopy(bytes, 0, data, 0, bytes.length);

		for (int i = bytes.length; i < size; i++) {
			data[i] = fillByte;
		}

		return data;
	}
	/**
	 * ByteArray를 Size크기 만큼 생성하고 fillByte값으로 모두 채운다.0ㅔ
	 * @param fillByte
	 * @param size
	 * @return
	 */
	public static byte[] fillBytes(byte fillByte, int size){
		byte[] data = new byte[size];
		for (int i = 0; i < size; i++) {
			data[i] = fillByte;
		}
		return data;
	}
	
	/**
     * 7byte의 raw 데이터를 입력 받아 yyyymmddhhmmss로 변형해 리턴
     * @param timestamp - 7byte의 timestamp
     * @return yyyymmddhhmmss의 형태로 리턴
     */
    public static String getTimeStamp(byte[] timestamp) {
        int year = getIntToBytes(new byte[]{timestamp[0], timestamp[1]});
        int month = getIntToByte(timestamp[2]);
        int day = getIntToByte(timestamp[3]);
        int hour = getIntToByte(timestamp[4]);
        int minute = getIntToByte(timestamp[5]);
        int second = getIntToByte(timestamp[6]);
        return "" + (year) + (month < 10 ? "0" + month : month) + (day < 10 ? "0" + day : day) + (hour < 10 ? "0" + hour : hour) + (minute < 10 ? "0" + minute : minute) + (second < 10 ? "0" + second : second);
    }
    
    /**
     * 5byte의 raw 데이터를 입력 받아 yyyymmddhhmm 형태로 리턴함
     * @param timestamp - 5byte의 timestaamp(year는 200년 이후로 지난 년수)
     * @return
     */
    public static String getTimeStamp5(byte[] timestamp) {
        int year = getIntToByte(timestamp[0]);
        int month = getIntToByte(timestamp[1]);
        int day = getIntToByte(timestamp[2]);
        int hour = getIntToByte(timestamp[3]);
        int minute = getIntToByte(timestamp[4]);
        
        return "" + (year + 2000) + (month < 10 ? "0" + month : month) + (day < 10 ? "0" + day : day) + (hour < 10 ? "0" + hour : hour) + (minute < 10 ? "0" + minute : minute);
    }
    
    public static byte[] getTimeStamp7Bytes(String yyyymmddhhmmss) {
        if(yyyymmddhhmmss.length() < 14) {
            yyyymmddhhmmss = StringUtil.endAppendNStr('0', yyyymmddhhmmss, 14);
        }
    	
		String yyyy = yyyymmddhhmmss.substring(0, 4);
		String month = yyyymmddhhmmss.substring(4, 6);
		String dd = yyyymmddhhmmss.substring(6, 8);
		String hh = yyyymmddhhmmss.substring(8, 10);
		String minute = yyyymmddhhmmss.substring(10,12);
		String ss = yyyymmddhhmmss.substring(12, 14);
		
		byte[] dateTimeBytes = new byte[] {};
		dateTimeBytes = DataUtil.append(dateTimeBytes, DataUtil.get2ByteToInt(yyyy));
		dateTimeBytes = DataUtil.append(dateTimeBytes, new byte[] {DataUtil.getByteToInt(month)} );
		dateTimeBytes = DataUtil.append(dateTimeBytes, new byte[] {DataUtil.getByteToInt(dd)} );
		dateTimeBytes = DataUtil.append(dateTimeBytes, new byte[] {DataUtil.getByteToInt(hh)} );
		dateTimeBytes = DataUtil.append(dateTimeBytes, new byte[] {DataUtil.getByteToInt(minute)} );
		dateTimeBytes = DataUtil.append(dateTimeBytes, new byte[] {DataUtil.getByteToInt(ss)} );
		
        return dateTimeBytes;
    }
    
    /**
     * 실시간 검침 포맷의 sigExp의 지수부를 계산해 리턴함
     * @param sigExp
     * @return
     */
    public static Float getExp(byte sigExp) {               
        int scaleSign;
        if(((sigExp&0x40)>>>6)==1){
            scaleSign=-1;
        }else {
            scaleSign=1;
        }
        int scaleValue = (sigExp&0x3f);     
        return (float) Math.pow(10, scaleSign*scaleValue);
    }
    
    /**
     * 실시간 검침 포맷의 value 부분의 sign 여부를 리턴함
     * @param sigExp
     * @return
     */
    public static boolean isSigned(byte sigExp) {               
        if(((sigExp&0x80)>>>7)==1){
            return true;
        }else {
            return false;
        }       
        
    }
    
    public static byte[] readByteString(String byteString) {
        byte[] result = new byte[byteString.length() / 2];
        int index = 0;

        while (index < result.length) {
            result[index] = (byte) Short.parseShort(byteString.substring(index * 2, index * 2 + 2), 16);
            index++;
        }

        return result;
    }
    
    /**
     * byte => bit(00000000) 변환
     * @param sigExp
     * @return
     */
    public static String getBit(byte attr) {
	   		String sBit = Integer.toBinaryString(DataUtil.getIntToByte(attr));
	   		int cnt = sBit.length();
	   		if(cnt<8){
	   			for(int i=cnt;i<8;i++){
	   				sBit= "0"+sBit;
	   			}
	   		}
 	        return sBit;
    }
    /**
     * code bit 정수값 계산.
     * @param sigExp
     * @return
     */
    public static String getBitToInt(String val , String fmt) {
   	  double bit = 0;
         for (int i=val.length()-1; i >=0;i--){
       	  if("1".equals(String.valueOf(val.charAt(i)))){
       		  bit = bit +Math.pow(2, (val.length()-i-1));  
       	  }
         }
         return String.format(fmt, Math.round(bit));
    }
    
    public static byte[] obisTobyteArray(String obisCode){
    	String[] code = obisCode.replace(".", ":").split(":");
		byte[] obisArray = new byte[]{};
		for(String s : code){
			obisArray = DataUtil.append(obisArray, new byte[]{DataUtil.getByteToInt(Integer.parseInt(s))});
		}

		return obisArray;
    }
    
    public static String convertObis(String obisCode) {
    	String returnData = "";
		byte[] obisCodeArr = Hex.encode(obisCode);
		obisCode="";
		for (int i = 0; i < obisCodeArr.length; i++) {
			if(i == 0) {
				obisCode += DataUtil.getIntToByte(obisCodeArr[i]);
			} else {
				obisCode += "."+DataUtil.getIntToByte(obisCodeArr[i]);
			}
		}
		returnData = obisCode;
    	return returnData;
    }

    public static short getShortTo2Byte(byte[] b)
    {
		short val =   (short) (((b[0] & 0xff) << 8)
	            + (b[1] & 0xff));
		return val;
    }
    
    // INSERT START SP-1154
	public static String makeHANConfigObjectValue(int bitPosition, String setValue, String currentValue) {
		int currentVal = Integer.parseInt(currentValue);
		
		int writeBit = 0;
		String setConfObj = "";
		if (setValue.equals("1")) {
			writeBit = 1 << bitPosition;
			setConfObj = String.valueOf(currentVal |= writeBit);
		} else {
			writeBit = ~(1 << bitPosition);
			setConfObj = String.valueOf(currentVal &= writeBit);
		}
		
		return setConfObj;
	}
    // INSERT END SP-1154
    
}
