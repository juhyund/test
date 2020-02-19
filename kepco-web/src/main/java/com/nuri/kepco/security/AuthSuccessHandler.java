package com.nuri.kepco.security;

import java.io.IOException;
import java.util.Collection;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.springframework.security.core.Authentication;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.web.authentication.SimpleUrlAuthenticationSuccessHandler;
import org.springframework.stereotype.Component;

@Component
public class AuthSuccessHandler extends SimpleUrlAuthenticationSuccessHandler {
	
	@Override
	public void onAuthenticationSuccess(HttpServletRequest request, HttpServletResponse response,
			Authentication authentication) throws ServletException, IOException {

		// 1. user 정보 확인
		SecurityUser user = (SecurityUser) authentication.getPrincipal();
		
		HttpSession session = request.getSession();

		response.setStatus(HttpServletResponse.SC_OK);

		Collection<? extends GrantedAuthority> roles = authentication.getAuthorities();	// Granted Authorities:
																						// ROLE_SUPER
		// 2. role 확인: role에 따른 메뉴페이지 리다이렉팅.
		if (roles.contains(SecurityUser.ROLE_SUPER)) {
			session.setAttribute("mode", "super");
			response.sendRedirect(request.getContextPath() + "/index");
		} else if (roles.contains(SecurityUser.ROLE_ADMIN)) {
			session.setAttribute("mode", "admin");
			response.sendRedirect(request.getContextPath() + "/index");
		} else {
			response.sendRedirect(request.getContextPath() + "/index");
		}
	}
}
