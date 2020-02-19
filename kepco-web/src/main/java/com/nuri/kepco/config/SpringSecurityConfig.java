package com.nuri.kepco.config;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.MessageSource;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.support.ReloadableResourceBundleMessageSource;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.authentication.configuration.EnableGlobalAuthentication;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.builders.WebSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.validation.beanvalidation.LocalValidatorFactoryBean;

import com.nuri.kepco.security.AuthFailureHandler;
import com.nuri.kepco.security.AuthSuccessHandler;
import com.nuri.kepco.security.AuthUserDetailsService;

@Configuration
@EnableWebSecurity
@EnableGlobalAuthentication
public class SpringSecurityConfig extends WebSecurityConfigurerAdapter {

	@Autowired
	AuthSuccessHandler successHandler;

	@Autowired
	AuthFailureHandler failureHandler;

	@Autowired
	AuthUserDetailsService userDetailsService;

	/**
	 * 자원 접근 권한 해제.
	 */
	@Override
	public void configure(WebSecurity web) throws Exception {
		web.ignoring().antMatchers("/commons/**", "/views/**");
	}

	@Override
	protected void configure(HttpSecurity http) throws Exception {

		http.csrf().disable().authorizeRequests() // 1. 인증이 된 요청에 대해서만 요청을 허용한다.
				// 권한 설정 - Matcher가 선언된 순서대로.
				// hasRole() 을 사용하면 ROLE_을 접두사로 지정하지 않아도 됨.
				// Request Path에 대한 권한 지정(파일 경로가 아님)
				.antMatchers("/login", "/error/**", "/kicp/**", "/nuri/**").permitAll() // 사용자가 접근할 수 있는 여러개의 URL 패턴 지정.
				.antMatchers("/**/*").hasAnyRole("SUPER", "ADMIN", "USER").anyRequest().authenticated() // 일치하지 않는 URL의 경우
																										// 사용자 인증을 요구.
				.and().formLogin() // 2. 폼 기반 로그인으로 인증한다.
				.loginPage("/login") // 로그인 Form 커스텀 페이지 설정.
				.usernameParameter("user_id").passwordParameter("user_pass").permitAll() // 모든 사용자에게 로그인 페이지 접속을 허용함.(폼
																							// 기반 로그인과 관련된 모든 URL에 허용)
				.successHandler(successHandler).failureHandler(failureHandler).and().logout().permitAll().and()
				.httpBasic(); // 3. 사용자는 Http 기반으로 인증한다.

		/**
		 * 로그아웃 설정.
		 */
		http.logout() // WebSecurityConfigurerAdapter 사용시 자동 지원.
				.logoutSuccessUrl("/login") // 로그아웃 이후 URL. default는 /login
				.invalidateHttpSession(true); // 로그아웃 시 HttpSession 무효화 여부 결정.
		
		/**
		 * 동일 domain에서 iframe 접근이 가능하도록 설정
		 */
		http.headers().frameOptions().sameOrigin();
		;
	}

	/**
	 * BCryptPasswordEncoder - Spring Security에서 기본적으로 사용하는 암호화 방식. - salt를 입력받지 않고
	 * 암호화 되는 과정에서 랜덤된 키값을 이용해 암호화하여 매번 새로운 값을 만들어 줌. => 랜덤의 salt를 부여하여 여러 번 해시를 적용.
	 */
	@Bean
	public PasswordEncoder passwordEncoder() {
		return new BCryptPasswordEncoder();
	}

	/**
	 * Defining the MessageSource Bean - custom message를 작성한 파일을 MessageSource로 등록하여
	 * 사용할 수 있도록 한다.
	 * 
	 * @return MessageSource
	 */
	@Bean
	public MessageSource messageSource() {
		ReloadableResourceBundleMessageSource messageSource = new ReloadableResourceBundleMessageSource();
		messageSource.setBasename("classpath:security-messages");
		messageSource.setDefaultEncoding("UTF-8");
		return messageSource;
	}

	/**
	 * AuthenticationManager 생성.
	 */
	@Override
	protected void configure(AuthenticationManagerBuilder auth) throws Exception {
		auth.userDetailsService(userDetailsService).passwordEncoder(passwordEncoder());
	}

	/**
	 * Defining LocalValidatorFactoryBean - 프로퍼티에 정의된 custom message를 사용하기 위해
	 * MessageSource와 LocalValidatorFactoryBean 설정.
	 * 
	 * @return LocalValidatorFactoryBean
	 */
	@Bean
	public LocalValidatorFactoryBean getValidator() {
		LocalValidatorFactoryBean bean = new LocalValidatorFactoryBean();
		bean.setValidationMessageSource(messageSource());
		return bean;
	}
}
