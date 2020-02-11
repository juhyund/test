package com.aimir.fep.protocol.fmp.datatype;

import org.apache.mina.core.buffer.IoBuffer;

import com.aimir.util.Hex;

public class HEX extends FMPNonFixedVariable
{
    /**
     * constructor
     */
    public HEX() 
    {
    }

    /**
     * constructor
     *
     * @param len <code>int</code> length of byte array
     */
    public HEX(int len)
    {
        this.value = new byte[len];
        this.len = len;
        this.isFixed = true;
    }

    /**
     * constructor
     *
     * @param value <code>String</code> String
     */
    public HEX(String value)
    {
        this.value = Hex.encode(value);
        this.len = this.value.length;
        this.isFixed = true;
    }

    /**
     * constructor
     *
     * @param value <code>byte[]</code> byte array
     */
    public HEX(byte[] value)
    {
        this.value = value;
        this.len  = value.length;
        this.isFixed = true;
    }

    /**
     * get HEX String
     *
     * @return value <code>String</code> HEX String
     */
    public String getValue()
    {
        return Hex.decode(this.value);
    }

    /**
     * set HEX Value String
     *
     * @param value <code>String</code> HEX String
     */
    public void setValue(String value)
    {
        if(isFixed)
        {
            byte[] bx = Hex.encode(value);
            if(bx.length >= this.len)
                System.arraycopy(bx,0,this.value,0,this.len);
            else
                System.arraycopy(bx,0,this.value,0,bx.length);
        } else {
            this.value = Hex.encode(value);
            this.len = this.value.length;
        }
    }

    /**
     * set HEX Value Byte array
     *
     * @param value <code>byte[]</code> HEX value byte array
     */
    public void setValue(byte[] value)
    {
        if(isFixed)
        {
            if(value.length >= this.len)
                System.arraycopy(value,0,this.value,0,this.len);
            else
                System.arraycopy(value,0,this.value,0,value.length);
        } else {
            this.value = value;
        }
    }

    /**
     * encode HEX Value
     *
     * @return value <code>byte[]</code> encoded byte array
     */
    public byte[] encode()
    { 
        return this.value;
    }

    /**
     * encode HEX Value
     *
     * @param iscompact <code>boolean</code>
     * @return value <code>byte[]</code> encoded byte array
     */
    public byte[] encode(boolean iscompact)
    {
        return encode();
    }

    /**
     * decode HEX Value
     *
     * @param buff <code>IoBuffer</code> input bytebuffer
     * @param size <code>int</code> BCD Value length
     */
    public void decode(String ns, IoBuffer buff,int size)
    {
        byte[] bx = new byte[size];
        buff.get(bx,0,bx.length);
        setValue(bx);
    }

    /**
     * decode HEX Value
     *
     * @param buff <code>IoBuffer</code> input bytebuffer
     */
    public void decode(String ns, IoBuffer buff)
    {
        if(isFixed && (this.value != null) && (this.value.length > 0))
            buff.get(this.value,0,this.value.length);
    }

    public int decode(String ns, byte[] buff,int pos)
    {
        System.arraycopy(buff,pos,this.value,0,this.value.length);
        return this.value.length;
    }

    public int decode(String ns, byte[] buff,int pos,int size)
    {
        this.value = new byte[size];
        System.arraycopy(buff,pos,this.value,0,this.value.length); 
        return size;
    }

    /**
     * get syntax(data type)
     *
     * @return syntax <code>int</code> syntax
     */
    public int getSyntax()
    {
        return DataType.HEX;
    }

    /**
     * get java syntax
     *
     *@returnsyntax<code>String</code>
     */
    public String getJavaSyntax()
    {
        return String.class.getName();
    }

    public String getMIBName() { return "eui64Entry"; }

    /**
     * get HEX String Value
     *
     * @return value <code>String</code>
     */
    public String toString()
    {
        return Hex.decode(this.value);
    }
}
