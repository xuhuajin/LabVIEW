<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="16008000">
	<Item Name="我的电脑" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">我的电脑/VI服务器</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">我的电脑/VI服务器</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="编码盘.ctl" Type="VI" URL="../编码盘.ctl"/>
		<Item Name="电机控制.vi" Type="VI" URL="../电机控制.vi"/>
		<Item Name="发送PID.vi" Type="VI" URL="../发送PID.vi"/>
		<Item Name="发送数据打包-八位校验和.vi" Type="VI" URL="../发送数据打包-八位校验和.vi"/>
		<Item Name="获取PID参数.vi" Type="VI" URL="../获取PID参数.vi"/>
		<Item Name="获取实际值.vi" Type="VI" URL="../获取实际值.vi"/>
		<Item Name="获取指令字节.vi" Type="VI" URL="../获取指令字节.vi"/>
		<Item Name="控件 2.ctl" Type="VI" URL="../控件 2.ctl"/>
		<Item Name="通讯协议解析.vi" Type="VI" URL="../通讯协议解析.vi"/>
		<Item Name="转盘.ctl" Type="VI" URL="../转盘.ctl"/>
		<Item Name="依赖关系" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
			</Item>
			<Item Name="PID转换.vi" Type="VI" URL="../PID转换.vi"/>
		</Item>
		<Item Name="程序生成规范" Type="Build">
			<Item Name="我的应用程序" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{3B23A260-D2FD-4BB6-B2EB-5EC802AC6304}</Property>
				<Property Name="App_INI_GUID" Type="Str">{CED5CB5A-9C97-43D7-A3B3-13B05551D57C}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{6FBEDDFA-0E9E-4463-A030-188241F29CD9}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">我的应用程序</Property>
				<Property Name="Bld_defaultLanguage" Type="Str">ChineseS</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../exe</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToProject</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{1DBB3D99-78FD-421F-8843-7186260F808A}</Property>
				<Property Name="Bld_version.build" Type="Int">4</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">电机调试控制.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../exe/电机调试控制.exe</Property>
				<Property Name="Destination[0].path.type" Type="Str">relativeToProject</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">支持目录</Property>
				<Property Name="Destination[1].path" Type="Path">../exe/data</Property>
				<Property Name="Destination[1].path.type" Type="Str">relativeToProject</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{36EACC54-E14A-449F-8440-23D8F4A22FB0}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/我的电脑/电机控制.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
				<Property Name="TgtF_companyName" Type="Str">徐华金</Property>
				<Property Name="TgtF_fileDescription" Type="Str">我的应用程序</Property>
				<Property Name="TgtF_internalName" Type="Str">我的应用程序</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">版权 2021 徐华金</Property>
				<Property Name="TgtF_productName" Type="Str">电机控制</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{FCC69AFB-2410-4FEC-9757-C9F4BD47535D}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">电机调试控制.exe</Property>
			</Item>
		</Item>
	</Item>
</Project>
