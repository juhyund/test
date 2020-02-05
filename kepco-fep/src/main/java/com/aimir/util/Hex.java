package com.aimir.util;



public class Hex {
 //   private static Log log = LogFactory.getLog(Hex.class);

    private static final char[] DIGITS = {
        '0', '1', '2', '3', '4', '5', '6', '7',
           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };

    /**
     *  encode
     *
     * @param data <code>String</code> Hex String
     * @return result <code>byte[]</code>
     */
    public static byte[] encode(String data)
    { 
        data = data.trim();
       	if(data.length()%2!=0)
            data=data+"0";
        char[] chars = data.toUpperCase().toCharArray();
        int len = chars.length; 
        if ((len & 0x01) != 0) { 
           // log.info("Odd number of characters."); 
        }
        byte[] out = new byte[len >> 1];
        // two characters form the hex value.
        for (int i = 0, j = 0; j < len; i++) {
            int f = toDigit(chars[j], j) << 4;
            j++;
            f = f | toDigit(chars[j], j);
            j++;
            out[i] = (byte) (f & 0xFF);
        }
        return out;
    }
    protected static int toDigit(char ch, int index) 
    { 
        int digit = Character.digit(ch, 16); 
        if (digit == -1) { 
            //log.info("Illegal hexadecimal charcter " + ch + " at index " + index); 
        }
        return digit;
    }

    /**
     *  decode
     *
     * @param data <code>byte[]</code> Hex String
     * @return result <code>String</code>
     */
    public static String decode(byte[] data) 
    { 
        if(data == null)
            return "";

        int l = data.length; 
        char[] out = new char[l << 1]; 
        // two characters form the hex value.  
        for (int i = 0, j = 0; i < l; i++) { 
            out[j++] = DIGITS[(0xF0 & data[i]) >>> 4 ]; 
            out[j++] = DIGITS[ 0x0F & data[i] ]; 
        } 
        return new String(out);
    }
    
    //10진수를 16진수 변환ㄴ
    public static String longtohex(byte[] data){
    	  StringBuffer buf = new StringBuffer();
    	 for(int i=0; i < data.length; i++){
     		if(Integer.toHexString(data[i]).equals("2e")){
 				buf.append("00");
 			}else{
 				buf.append(Integer.toHexString(data[i]));
 			}
         }
    	 
    	 return buf.toString();
    }
    
    public static String hexToAscii(String hexStr) {
        StringBuilder output = new StringBuilder("");
         
        for (int i = 0; i < hexStr.length(); i += 2) {
            String str = hexStr.substring(i, i + 2);
            output.append((char) Integer.parseInt(str, 16));
        }
         
        return output.toString();
    }

    /**
     *  decode
     *
     * @param data <code>byte[]</code> Hex String
     * @return result <code>String</code>
     */
    public static String decode(byte[] data,int pos,int len) 
    { 
        if(data == null)
            return "";

        //int l = data.length; 
        char[] out = new char[len << 1]; 
        // two characters form the hex value.  
        for (int i = pos, j = 0; i < len; i++) { 
            out[j++] = DIGITS[(0xF0 & data[i]) >>> 4 ]; 
            out[j++] = DIGITS[ 0x0F & data[i] ]; 
        } 
        return new String(out);
    }
    
    /**
     * Transform to with empty String. <p>
     * For Logging <p>
     * ex)  0x09 0x81 --> "09 81"
     * @param b byte array b
     * @return
     */
    public static String getHexDump(byte[] b){
        
        StringBuffer buf = new StringBuffer();
        
        try{
            for(int i = 0; i < b.length; i++) {
                int val = b[i];
                val = val & 0xff;
                buf.append(frontAppendNStr('0',Integer.toHexString(val),2)+" ");
                if(((i+1)%24) == 0) buf.append('\n');
            }
        }catch(Exception e){
            
        }
        return buf.toString();
    }
    
    /**
     * @param append source of String
     * @param str   to append  
     * @param length
     * @return
     */
    public static String frontAppendNStr(char append, String str, int length)
    {
        StringBuffer b = new StringBuffer("");

        try {
            if(str.length() < length)
            {
               for(int i = 0; i < length-str.length() ; i++)
                   b.append(append);
               b.append(str);
            }
            else
            {
                b.append(str);
            }
        } catch(Exception e) {
            
        }
        return b.toString();
    }
    
    public static int getBigEndian(byte[] v)throws Exception{
        int[] arr = new int[4];
        for(int i=0;i<4;i++){
             arr[i] = (int)(v[3-i] & 0xFF);
        }
        return ((arr[0]  << 24) + (arr[1]  << 16) + (arr[2]  << 8) + (arr[3]  << 0));
    }
    
    public static  byte[] intToByteArray(int value) {
		byte[] byteArray = new byte[4];
		byteArray[0] = (byte)(value >> 24);
		byteArray[1] = (byte)(value >> 16);
		byteArray[2] = (byte)(value >> 8);
		byteArray[3] = (byte)(value);
		return byteArray;
	}

	public static Float getFloatByByte(byte[] param) {
		Long i = Long.parseLong(Hex.decode(param), 16);
		Float f = Float.intBitsToFloat(i.intValue());
		
		return f;
	}
	
	public static Long getLongByByte(byte[] param) {
		 return Long.parseLong(Hex.decode(param), 16);
	}
 
}
