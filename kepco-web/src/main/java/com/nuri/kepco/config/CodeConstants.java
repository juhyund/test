package com.nuri.kepco.config;

import lombok.Getter;

public class CodeConstants {

	@Getter
	public enum PREFIX_CONSTANTS {
		LOG_PREFIX_CONNECTIVITY("LPCV", "CONNECTIVITY 서버가 로그 시퀀스를 발급"),
		LOG_PREFIX_COMMAND_MANAGER("LPCM", "COMMAND MANGER 서버가 로그 시퀀스를 발급"),
		LOG_PREFIX_API("LPAI", "API 서버가 로그 시퀀스를 발급"),
		LOG_PREFIX_MESSAGE("LPMA", "MESSAGE 서버가 로그 시퀀스를 발급"),		
		LOG_PREFIX_ADMIN_POTAL("LPAP", "ADMIN-POTAL 서버가 로그 시퀀스를 발급"),
		LOG_PREFIX_SERVICE_POTAL("LPSP", "SERVICE-POTAL 서버가 로그 시퀀스를 발급"),
		
		KEY_TRANSACTION_API("KTA", "API 서버가 다운링크의 트랜잭션 발급"),
		
		CLIKEY_PREFIX_CONNECTIVITY("CKPCV", "CONNECTIVITY 클라이언트 키 prefix"),
		CLIKEY_PREFIX_COMMAND_MANAGER("CKPCM", "COMMAND MANGER 클라이언트 키 prefix"),
		CLIKEY_PREFIX_API("CKPAI", "API 클라이언트 키 prefix"),
		CLIKEY_PREFIX_MESSAGE("CKPMS", "MESSAGE 클라이언트 키 prefix"),
		CLIKEY_PREFIX_ADMIN_POTAL("CKPAP", "ADMIN-POTAL 클라이언트 키 prefix"),
		CLIKEY_PREFIX_SERVICE_POTAL("CKPSP", "SERVICE-POTAL 클라이언트 키 prefix"),
		
		SERKEY_PREFIX_CONNECTIVITY("SKPCV", "CONNECTIVITY 서버키 prefix"),
		SERKEY_PREFIX_COMMAND_MANAGER("SKPCM", "COMMAND MANGER 서버키 prefix"),
		SERKEY_PREFIX_API("SKPAI", "API 서버키 prefix"),
		SERKEY_PREFIX_MESSAGE("SKPMS", "MESSAGE 서버키 prefix"),
		SERKEY_PREFIX_ADMIN_POTAL("SKPAP", "ADMIN-POTAL 서버키 prefix"),
		SERKEY_PREFIX_SERVICE_POTAL("SKPSP", "SERVICE-POTAL 서버키 prefix"),
		
		SEQ_COMP_API("SCA", "COMP SEQ"),
		SEQ_MODEL_API("SMA", "MODEL SEQ"),
		SEQ_REGION_API("SRA", "REGION SEQ");
		
		public String prefix;
		public String desc;
		PREFIX_CONSTANTS(String prefix, String desc) {
			this.prefix = prefix;
			this.desc = desc; 
		}
	}
	
	@Getter 
	public enum DEVICE_STAT {
		NORMAL("DS001", "정상"),
		WAIT("DS002", "대기"),
		DE_REGISTER("DS003", "등록해제"),
		POWER_DOWN("DS004", "정전"),
		NEW_REGISTER("DS005", "등록"),
		DELETE("DS006", "삭제 (철거)");
		
		private String dcodeId;
		private String descr;
		DEVICE_STAT(String dcodeId, String descr) {
			this.dcodeId = dcodeId;
			this.descr = descr;
		}
	}
	
	@Getter
	public enum NODE_TYPE {
		GATEWAY("NT001", 1),
		MODEM("NT002", 2),
		SENSOR("NT003", 3),
		METER("NT004", 4);
		
		private String dcodeId;
		private int sort;
		NODE_TYPE(String dcodeId, int sort) {
			this.dcodeId = dcodeId;
			this.sort = sort;
		}
	}
	
	@Getter
	public enum OP_LIST {
		READ("OP001","READ"),
		WRITE("OP002","WRITE"),
		OBSERVE("OP003","OBSERVE"),
		OBSERVE_CANCEL("OP004","OBSERVE-CANCEL"),
		EXECUTE("OP005","EXECUTE"),
		WRITE_ATTRIBUTE("OP006","WRITE-ATTRIBUTE"),
		DISCOVER("OP007","DISCOVER"),
		CREATE("OP008","CREATE"),
		DELETE("OP009","DELETE"),
		SEND("OP010","SEND"),
		NOTIFY("OP011","NOTIFY"),
		REGISTRATION("OP012","REGISTRATION"),
		DE_REGISTRATION("OP013","DE-REGISTRATION");
		
		private String dcodeId;
		private String method;
		OP_LIST(String dcodeId, String method) {
			this.dcodeId = dcodeId;
			this.method = method;
		}
	}
	
	@Getter
	public enum FW_STATUS {
		FW000("소프트웨어파일전송"),
		FW001("업데이트 성공"),
		FW002("플래시 메모리 부족"),
		FW003("다운로드 프로세스 중 RAM 부족 "),
		FW004("다운로드 프로세스 중 연결이 끊김"),
		FW005("다운로드 된 새 패키지에 대한 무결성 검사 실패"),
		FW006("미지원 패키지 유형 "),
		FW007("잘못된 URI"),
		FW008("소프트웨어 업데이트 실패"),
		FW009("미지원 프로토콜");
		
		private String descr;
		FW_STATUS(String descr) {
			this.descr = descr;
		}
	}
	
	@Getter 
	public enum USE_YN {
		Y(1),
		N(0);
		
		private int code;
		USE_YN(int code) {
			this.code = code;
		}
	}
	
}
