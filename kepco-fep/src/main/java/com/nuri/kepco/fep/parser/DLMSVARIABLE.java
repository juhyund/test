package com.nuri.kepco.fep.parser;

public class DLMSVARIABLE {
	
	// METER TYPE
    public static byte METER_TYPE_0 = (byte)0x01;	// 한전 표준
    public static byte METER_TYPE_1 = (byte)0x02;	// E-Type 1.0
    public static byte METER_TYPE_2 = (byte)0x04;	// E-Type 1.1
    public static byte METER_TYPE_3 = (byte)0x08;	// G-Type
    public static byte METER_TYPE_4 = (byte)0x10;	// EA-Type
    
    // OBIS CODE ID
    public static byte OBIS_CODE_0 = (byte)0x01; 	// LP
    public static byte OBIS_CODE_1 = (byte)0x02;	// 현재검침
    public static byte OBIS_CODE_2 = (byte)0x04;	// 정기검침
    public static byte OBIS_CODE_3 = (byte)0x08;	// 정복전
    public static byte OBIS_CODE_4 = (byte)0x10;	// 최대부하
    public static byte OBIS_CODE_5 = (byte)0x20;	// 현재 최대수요
    public static byte OBIS_CODE_6 = (byte)0x40;	// G-Type순시전압전류
    public static byte OBIS_CODE_7 = (byte)0x80;	// Meter Info
    
    public enum OBIS {
    	
    	METER_TIME("0000010000FF", "Meter Time"),    	
    	CUSTOMER_ID("0100000000FF", "Customer meter ID"),	//Customer meter ID
    	MANUFACTURE_ID("0100000001FF", "Manufacturer meter ID"),	//Manufacturer meter ID
//    	COSEM_ID("00002A0000FF", "COSEM ID"),	//COSEM 계기 식별자
    	ACTIVEPOWER_CONSTANT("0101000300FF","ActivePower Constant"),	// 유효전력량 계기 정수
        REACTIVEPOWER_CONSTANT("0101000301FF","ReactivePower Constant"),	// 무효전력량 계기 정수
        APPRENTPOWER_CONSTANT("0101000302FF","ApparentPower Constant"),	// 피상전력량 계기 정수
        LP_INTERVAL("0101000804FF","LP INTERVAL"),	// LP 수집 주기
        MEASUREMENT_DATE("00000F0000FF","Measurement Date"),	// 정기검침일 
        ENERGY_LOAD_PROFILE("0100630100FF", "Load Profile"),	// Load Profile
        
        BILLING_PERIOD_COUNTER("0100000100FF", "Billing Period Counter"),	// 검침횟수
        BILLING_DATE("010000010200", "Monthly Billing Date"),	// 검침일자
        BILLING("000062010100", "Billing"),	// billing 0000620101VZ
        BILLING_REVERSE("000062010300", "Billing"),	// billing 역방향 0000620103VZ
        
        ETYPE_BILLING("010101080001", "EtypeBilling"), // ETYPE 정기검침
            	
        HW_VER("00002A0000FF", "METER VERSION");	// COSEM 계기 식별자
    
        private String code;
        private String name;
        
        OBIS(String code, String name) {
            this.code = code;
            this.name = name;
        }
        
        public String getCode() {
            return this.code;
        }
        
        public String getName() {
            return this.name;
        }
        
        public static OBIS getObis(String code) {
            for (OBIS obis : values()) {
                if (obis.getCode().equals(code)) return obis;
            }
            return null;
        }
    }
    
    public enum VENDOR {
        
    	SEOCHANG("05","Seochang","SEO"),
    	NAMJUNSA("08","Namjunsa","NAM"),
    	OMNISYSTEM("26","OmniSystem","OMN"),
    	NURITELECOM("47","Nuritelecom","NUR"),
    	DMPOWER("24","DMPower","DMP"),
    	ILJINELECTRIC("9","iljinelectric","ILJ"),
    	PSTEC("2","PSTEC","PST"),
    	WIZIT("6","WIZIT","WIZ"),
    	AMS("25","AmsTech","AMS"),
    	DURECOM("39","durecom","DRC"),
    	YPP("36","YPP","YPP"),
    	PowerPlusCom("35","PowerPlusCom","PPC"),
    	SHINHAN("56","SHINHAN","SHN")
    	;
                
        private String code;
        private String name;
        private String sname;
        
        VENDOR(String code, String name, String sname) {
            this.code = code;
            this.name = name;
            this.sname = sname;
        }
        
        public String getCode() {
            return this.code;
        }
        
        public String getName() {
            return this.name;
        }
        
        public String getSname() {
            return this.sname;
        }
        
        public static VENDOR getVendor(String code) {
            for (VENDOR vendor : values()) {
                if (vendor.getCode().equals(code)) return vendor;
            }
            return null;
        }
    }
    
    
    public enum METERTYPE {
    	
    	METERTYPE14("14","MT001"),	// Standard- Single Ph 2 wire 40(10)A
    	METERTYPE15("15","MT001"),	// Standard- Single Ph 2 wire 120(30)A
    	METERTYPE34("34","MT001"), // Standard- 3 Ph 4 wire 40(10)A
    	METERTYPE35("35","MT001"), // Standard- 3 Ph 4 wire 120(30)A
    	METERTYPE01("01","MT001"), // Standard- Single Ph 2 wire 5A
    	METERTYPE03("03","MT001"), // Standard- 3 Ph 4 wire 5A
    	
    	METERTYPE17("17","MT002"),	// E-Type  - bottom Type
    	METERTYPE18("18","MT002"),  // E-Type  - top bottom Type
    	
    	METERTYPE25("25","MT004"), // G-Type  - Single Ph 2 wire 100(10)A
    	METERTYPE27("27","MT004"), //  G-Type  - Single Ph 2 wire 120(10)A
    	METERTYPE45("45","MT004"), //  G-Type  - 3 Ph 4 wire 100(10)A
    	METERTYPE47("47","MT004"), //  G-Type  - 3 Ph 4 wire 120(10)A
    	METERTYPE37("37","MT004"), //  G-Type  - 3 Ph 3 wire 120(10)A
    	METERTYPE26("26","MT004"), // G-Type  - Single Ph 2 wire 5A
    	METERTYPE46("46","MT004"), //  G-Type  - 3 Ph 4 wire 5A
    	METERTYPE38("38","MT004"), // G-Type  - 3 Ph 3 wire 5A
    
    	METERTYPE19("19","MT003"), //  EA-Type - Single Ph 2 wire 50(5)A
    	
    	UNKNOWN("99","MT006");
    	        
        private String code;
        private String name;
        
        METERTYPE(String code, String name) {
            this.code = code;
            this.name = name;
        }
        
        public String getCode() {
            return this.code;
        }
        
        public String getName() {
            return this.name;
        }
        
        public static METERTYPE getMeterType(String code) {
            for (METERTYPE metertype : values()) {
                if (metertype.getCode().equals(code)) return metertype;
            }
            return null;
        }
    }
    
    
    public enum METERPHASE {
    	
    	METERPHASE14("14","MP014"),	// Standard- Single Ph 2 wire 40(10)A
    	METERPHASE15("15","MP015"),	// Standard- Single Ph 2 wire 120(30)A
    	METERPHASE34("34","MP034"), // Standard- 3 Ph 4 wire 40(10)A
    	METERPHASE35("35","MP035"), // Standard- 3 Ph 4 wire 120(30)A
    	METERPHASE01("01","MP001"), // Standard- Single Ph 2 wire 5A
    	METERPHASE03("03","MP003"), // Standard- 3 Ph 4 wire 5A
    	
    	METERPHASE17("17","MP017"),	// E-Type  - bottom Type
    	METERPHASE18("18","MP018"),  // E-Type  - top bottom Type
    	
    	METERPHASE25("25","MP025"), // G-Type  - Single Ph 2 wire 100(10)A
    	METERPHASE27("27","MP027"), //  G-Type  - Single Ph 2 wire 120(10)A
    	METERPHASE45("45","MP045"), //  G-Type  - 3 Ph 4 wire 100(10)A
    	METERPHASE47("47","MP047"), //  G-Type  - 3 Ph 4 wire 120(10)A
    	METERPHASE37("37","MP037"), //  G-Type  - 3 Ph 3 wire 120(10)A
    	METERPHASE26("26","MP026"), // G-Type  - Single Ph 2 wire 5A
    	METERPHASE46("46","MP046"), //  G-Type  - 3 Ph 4 wire 5A
    	METERPHASE38("38","MP038"), // G-Type  - 3 Ph 3 wire 5A
    
    	METERPHASE19("19","MP019"), //  EA-Type - Single Ph 2 wire 50(5)A
    	UNKNOWN("99","MP099"); // UNKNOWN
    	        
        private String code;
        private String name;
        
        METERPHASE(String code, String name) {
            this.code = code;
            this.name = name;
        }
        
        public String getCode() {
            return this.code;
        }
        
        public String getName() {
            return this.name;
        }
        
        public static METERPHASE getMeterPhase(String code) {
            for (METERPHASE meterphase : values()) {
                if (meterphase.getCode().equals(code)) return meterphase;
            }
            return null;
        }
    }

    public final static String UNDEFINED = "undefined";

    public enum METER_CONSTANT {
        ActiveC,
        ReactiveC;
    }
    
    public enum ENERGY_LOAD_PROFILE {
    	
    	Array(0, "Array"),
    	Structure(1, "Structure"),
        ImportActiveEnergy(2, "importActiveEnergy"),	// 순방향 유효
        ImportLagReactive(3, "importLagReactive"),	// 순방향 지상 무효
        ImportLeadReactive(4, "importLeadReactive"),	// 순방향 진상 무효
        ImportApprentEnergy(5, "importApprentEnergy"),	// 순방향 피상전력   
        Date(6, "Date"),
        Status(7, "Status");	// 역방향 피상전력
        
        private int code;
        private String name;
        
        ENERGY_LOAD_PROFILE(int code, String name) {
            this.code = code;
            this.name = name;
        }
        
        public int getCode() {
            return this.code;
        }
        
        public String getName(){
            return this.name;
        }
    }    
    
    public enum DLMS_CLASS {
        DATA(1),
        REGISTER(3),
        EXTEND_REGISTER(4),
        DEMAND_REGISTER(5),
        REGISTER_ACTIVATION(6),
        PROFILE_GENERIC(7),
        CLOCK(8),
        SCRIPT_TABLE(9),
        SCHEDULE(10),
        SPECIAL_DAY(11),
        ACTIVITY_CALENDAR(20),
        ASSOCIATION_LN(15),
        ASSOCIATION_SN(12),
        REGISTER_MONITOR(21),
        SAP_ASSIGN(17),
        UTILITY_TABLE(26),
        SINGLE_ACTION_SCHEDULE(22),
        RELAY_CLASS(70),
    	LIMITER_CLASS(71),
    	MBUS_CLIENT_CLASS(72);
        
        private int clazz;
        
        DLMS_CLASS(int clazz) {
            this.clazz = clazz;
        }
        
        public int getClazz() {
            return this.clazz;
        }
    }
    
    public enum DLMS_CLASS_ATTR {
        DATA_ATTR01(2),            // value
        DATA_ATTR04(4),
        DATA_ATTR06(6),
        DATA_ATTR07(7),
        DATA_ATTR09(9),
        DATA_ATTR12(12),
        REGISTER_ATTR02(2),        // value
        REGISTER_ATTR03(3),        // scalar unit
        REGISTER_ATTR04(4),        // status
        REGISTER_ATTR05(5),        // 
        PROFILE_GENERIC_ATTR04(4),        // value
        PROFILE_GENERIC_ATTR02(2), // buffer
        PROFILE_GENERIC_ATTR03(3),	// capture object (for SAT)
        PROFILE_GENERIC_ATTR07(7), // entries in use
        PROFILE_GENERIC_ATTR08(8), // profile_entries
        CLOCK_ATTR02(2),
        CLOCK_ATTR05(5),        
    	CLOCK_ATTR07(7),
    	LIMIT_ATTR04(4),
    	LIMIT_ATTR06(6),
    	LIMIT_ATTR07(7),
        SCRIPT_TABLE_ATTR01(1),
        SCRIPT_TABLE_ATTR02(2),
        SINGLE_ACTION_SCHEDULE_ATTR04(4); // execution_time, array;
        
        private int attr;
        
        DLMS_CLASS_ATTR(int attr) {
            this.attr = attr;
        }
        
        public int getAttr() {
            return this.attr;
        }
    }

    public enum DLMS_TAG_TYPE {
        Null(0, 1),
        Array(1, 1),
        CompactArray(19, 1),
        Structure(2, 1),
        Enum(22, 1),
        Group(128, 1),
        BitString(4, 4),
        OctetString(9, 0),
        VisibleString(10, 0),
        BCD(13, 1),
        Boolean(3, 1),
        INT8(15, 1),
        UINT8(17, 1),
        INT16(16, 2),
        UINT16(18, 2),
        INT32(5, 4),
        UINT32(6, 4),
        FLOAT32(23, 4),
        INT64(20, 8),
        UINT64(21, 8),
        Datetime(25, 12),
        Date(26, 5),
        Time(27, 4);
        
        private int value;
        private int len;
        
        DLMS_TAG_TYPE(int value, int len) {
            this.value = value;
            this.len = len;
        }
        
        public int getValue() {
            return this.value;
        }
        
        public int getLenth() {
            return this.len;
        }
    }
    
        
    public DLMSVARIABLE() {

    }

    public static String getDataName(OBIS obis, int cnt, int structure) {
    	
  		if (obis == OBIS.ENERGY_LOAD_PROFILE) { // load profile
            for (ENERGY_LOAD_PROFILE profile : ENERGY_LOAD_PROFILE.values()) {
                if (profile.getCode() == (cnt % 8))
                    return profile.name();
            }
        }
  		
        return UNDEFINED+" ["+cnt+"]";
    }

    public enum UNIT {
        YEAR(1,"year[a]"),
        MONTH(2,"month[mo]"),
        WEEK(3,"week[wk]"),
        DAY(4,"day[d]"),
        HOUR(5,"hour[h]"),
        MINUTE(6,"min[min.]"),
        SECOND(7,"second[s]"),
        PHASE_ANGLEGEGREE(8,"phase anglegegree[°]"),
        TEMPERATURE(9,"temperature[°C]"),
        LOCAL_CURRENCY(10,"local currency[currency]"),
        LENGTH(11,"length[m]"), 
        SPEED(12,"speed[m/s]"), 
        VOLUME_CUBIC_METER(13,"volume cubic meter[m3]"),
        CORRECTED_VOLUME(14,"corrected volume[m3]"),
        VOLUME_FLUX_HOUR(15,"volume flux hour[m3/h]"),
        CORRECTED_VOLUME_FLUX_HOUR(16,"corrected vlume flux[m3/h]"),
        VOLUME_FLUXDAY(17,"volume flux[m3/d]"),
        CORRECTE_VOLUME_FLUX_DAY(18,"corrected vlume flux[m3/d]"),
        VOLUME_LITER(19,"volume[l]"),
        MASS_KG(20,"mass[kg]"),
        FORCE(21,"force[N]"),
        ENERGY(22,"energy[Nm]"),
        PRESSURE_PASCAL(23,"pressure_pascal[Pa]"),
        PRESSURE_BAR(24,"pressure[bar]"),
        ENERGY_JOULE(25,"energy_joule[J]"), // Energy joule J = Nm = Ws
        THERMAL_POWER(26,"thermal power[J/h]"), // Thermal power J/60*60s
        ACTIVE_POWER(27,"active power[W]"), //Active power P watt W = J/s
        APPARENT_POWER(28,"apparent power[VA]"), // Apparent power S
        REACTIVE_POWER(29,"reactive power[var]"), //Reactive power Q
        ACTIVE_ENERGY(30,"active energy[Wh]"), // Active energy W*60*60s
        APPARENT_ENERGY(31,"apparent energy[VAh]"), // Apparent energy VA*60*60s
        REACTIVE_ENERGY(32,"reactive energy[varh]"), // Reactive energy var*60*60s
        CURRENT(33,"current[A]"), // Current I ampere A
        ELECTRICAL_CHARGE(34,"voltage[C]"), // Electrical charge Q coulomb C = As
        VOLTAGE(35,"voltage[V]"), // Voltage
        ELECTRICAL_FIELD_STRENGTH(36,"electric field strength[V/m]"), // Electrical field strength E V/m
        CAPACITY(37,"capacitance[F]"), // Capacity C farad C/V = As/V
        RESISTANCE(38,"resistance[Ω]"), // Resistance R ohm = V/A
        RESISTIVITY(39,"resistivity[Ωm2/m]"), // Resistivity
        MAGNETIC_FLUX(40,"magnetic flux[Wb]"), // Magnetic flux F weber Wb = Vs
        INDUCTION(41,"magnetic flux densty[T]"), // Induction T tesla Wb/m2
        MAGNETIC(42,"magnetic field strength[A/m]"), // Magnetic field strength H A/m
        INDUCTIVITY(43,"inductance[H]"), // Inductivity L henry H = Wb/A
        FREQUENCY(44,"frequency[Hz]"), // Frequency f
        ACTIVE(45,"active[1/(Wh)]"), // Active energy meter constant 1/Wh
        REACTIVE(46,"reactive[1/(varh)]"), // Reactive energy meter constant
        APPARENT(47,"apparent[1/(VAh)]"), // Apparent energy meter constant
        V260(48,"v260[V2h]"), // V260*60s
        A260(49,"a260[A2h]"), // A260*60s
        MASS_KG_PER_SECOND(50,"mass flux[kg/s]"),
        CONDUCTANCE(51,"conductance[S, mho]"),
        KELVIN(52,"temperature[K]"),
        V2H(53,"v2h[1/(V2h)]"),
        A2H(54,"a2h[1/(A2h)]"),
        CUBIC_METER_RV(55,"cubic meter rv[1/m3]"),
        PERCENTAGE(56,"percentage[percentage]"),
        AMPERE_HOURS(57,"ampere-hours[Ah]"),
        ENERGY_PER_VOLUME(60,"energy per volume[Wh/m3]"),
        WOBBE(61,"wobbe[J/m3]"),
        MOLE_PERCENT(62,"mole percent[Mol %]"),
        MASS_DENSITY(63,"mass density[g/m3]"),
        PASCAL_SECOND(64,"pascal second[Pa s]"),
        JOULE_KILOGRAM(65,"joule kilogram[J/kg]"),
        SIGNAL_STRENGTH(70,"signal strength[dBm]"),
        RESERVED(253,"reserved"),
        OTHER_UNIT(254,"other"), 
        NO_UNIT(255,"unitless"); 
        
        private int code;
        private String unit;
        
        UNIT(int code, String unit) {
            this.code = code;
            this.unit = unit;
        }
        
        public String getName(){
        	return this.unit;
        }
        
        public int getCode() {
            return this.code;
        }
        
		public static UNIT getItem(int code) {
			for (UNIT fc : UNIT.values()) {
				if (fc.code == code) {
					return fc;
				}
			}
			return null;
		}
    }

    public static String getUnit(int unit) {

        if (unit == 1)
            return "a";
        else if (unit == 2)
            return "mo";
        else if (unit == 3)
            return "wk";
        else if (unit == 4)
            return "d";
        else if (unit == 5)
            return "h";
        else if (unit == 6)
            return "min.";
        else if (unit == 7)
            return "s";
        else if (unit == 8)
            return "°";
        else if (unit == 9)
            return "°C";
        else if (unit == 10)
            return "currency";
        else if (unit == 11)
            return "m";
        else if (unit == 12)
            return "m/s";
        else if (unit == 13)
            return "m3";
        else if (unit == 14)
            return "m3";
        else if (unit == 15)
            return "m3/h";
        else if (unit == 16)
            return "m3/h";
        else if (unit == 17)
            return "m3/d";
        else if (unit == 18)
            return "m3/d";
        else if (unit == 19)
            return "l";
        else if (unit == 20)
            return "kg";
        else if (unit == 21)
            return "N";
        else if (unit == 22)
            return "Nm";
        else if (unit == 23)
            return "Pa";
        else if (unit == 24)
            return "bar";
        else if (unit == 25)
            return "J";
        else if (unit == 26)
            return "J/h";
        else if (unit == 27)
            return "W";
        else if (unit == 28)
            return "VA";
        else if (unit == 29)
            return "var";
        else if (unit == 30)
            return "Wh";
        else if (unit == 31)
            return "VAh";
        else if (unit == 32)
            return "varh";
        else if (unit == 33)
            return "A";
        else if (unit == 34)
            return "C";
        else if (unit == 35)
            return "V";
        else if (unit == 36)
            return "V/m";
        else if (unit == 37)
            return "F";
        else if (unit == 38)
            return "Ω";
        else if (unit == 39)
            return "Ωm2/m";
        else if (unit == 40)
            return "Wb";
        else if (unit == 41)
            return "T";
        else if (unit == 42)
            return "A/m";
        else if (unit == 43)
            return "H";
        else if (unit == 44)
            return "Hz";
        else if (unit == 45)
            return "1/(Wh)";
        else if (unit == 46)
            return "1/(varh)";
        else if (unit == 47)
            return "1/(VAh)";
        else if (unit == 48)
            return "V2h";
        else if (unit == 49)
            return "A2h";
        else if (unit == 50)
            return "kg/s";
        else if (unit == 51)
            return "S, mho";
        else if (unit == 52)
            return "K";
        else if (unit == 53)
            return "1/(V2h)";
        else if (unit == 54)
            return "1/(A2h)";
        else if (unit == 55)
            return "1/m3";
        else if (unit == 56)
            return "percentage";
        else if (unit == 57)
            return "Ah";
        else if (unit == 60)
            return "Wh/m3";
        else if (unit == 61)
            return "J/m3";
        else if (unit == 62)
            return "Mol %";
        else if (unit == 63)
            return "g/m3";
        else if (unit == 64)
            return "Pa s";
        else if (unit == 253)
            return "reserved";
        else if (unit == 254)
            return "other";
        else if (unit == 255)
            return "unitless";
        else
            return "unitless";
    }
    
    public static String[] LP_STATUS_BIT = new String[]{
    	"Power down", //bit 7
    	"Not used",
    	"Clock adjusted",
    	"Not used",
    	"Daylight saving",
    	"Data not valid",
    	"Clock invalid",
    	"Critical error" //  bit 0
    };
}
