package com.nuri.dtlsproxy;

import java.io.UnsupportedEncodingException;

import com.penta.ptls.PreSharedKeyInterface;

public class PskManager implements PreSharedKeyInterface {

    @Override
    public byte[] getPreSharedKey(byte[] psk_id) {
        try {
            if (java.util.Arrays.equals(psk_id, "CLI_001".getBytes("UTF-8"))) {
                return new byte[] {
                    (byte) 0xAD, (byte) 0x89, (byte) 0xA3, (byte) 0x90, (byte) 0x93, (byte) 0x11, (byte) 0x02, (byte) 0xE5,
                    (byte) 0x39, (byte) 0x1D, (byte) 0x08, (byte) 0x32, (byte) 0x7B, (byte) 0xA4, (byte) 0x34, (byte) 0xE9
                };
            } else if (java.util.Arrays.equals(psk_id, "CLI_002".getBytes("UTF-8"))) {
                return new byte[] {
                    (byte) 0x39, (byte) 0x1D, (byte) 0x08, (byte) 0x32, (byte) 0x7B, (byte) 0xA4, (byte) 0x34, (byte) 0xE9,
                    (byte) 0xAD, (byte) 0x89, (byte) 0xA3, (byte) 0x90, (byte) 0x93, (byte) 0x11, (byte) 0x02, (byte) 0xE5
                };
            }else if (java.util.Arrays.equals(psk_id, "default1".getBytes("UTF-8"))) {
                return new byte[] {
                        (byte) 0x30, (byte) 0x30, (byte) 0x30, (byte) 0x30, (byte) 0x30, (byte) 0x30, (byte) 0x30, (byte) 0x30,
                        (byte) 0x30, (byte) 0x30, (byte) 0x30, (byte) 0x30, (byte) 0x30, (byte) 0x30, (byte) 0x30, (byte) 0x31
                    };
            }
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }

        return null;
    }

}