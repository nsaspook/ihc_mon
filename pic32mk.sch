<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.5.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="PIC32MK1024MCF100-I_PT">
<description>&lt;Microchip Technology MCU32, 120MHz, 4 I2C, 6 I2S, USB FS, CAN 2.0B, 12-bit ADC, Motor Control&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="QFP40P1400X1400X120-100N">
<description>&lt;b&gt;100-(PT) Quad Flatpack&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="-6.738" y="4.8" dx="1.475" dy="0.2" layer="1"/>
<smd name="2" x="-6.738" y="4.4" dx="1.475" dy="0.2" layer="1"/>
<smd name="3" x="-6.738" y="4" dx="1.475" dy="0.2" layer="1"/>
<smd name="4" x="-6.738" y="3.6" dx="1.475" dy="0.2" layer="1"/>
<smd name="5" x="-6.738" y="3.2" dx="1.475" dy="0.2" layer="1"/>
<smd name="6" x="-6.738" y="2.8" dx="1.475" dy="0.2" layer="1"/>
<smd name="7" x="-6.738" y="2.4" dx="1.475" dy="0.2" layer="1"/>
<smd name="8" x="-6.738" y="2" dx="1.475" dy="0.2" layer="1"/>
<smd name="9" x="-6.738" y="1.6" dx="1.475" dy="0.2" layer="1"/>
<smd name="10" x="-6.738" y="1.2" dx="1.475" dy="0.2" layer="1"/>
<smd name="11" x="-6.738" y="0.8" dx="1.475" dy="0.2" layer="1"/>
<smd name="12" x="-6.738" y="0.4" dx="1.475" dy="0.2" layer="1"/>
<smd name="13" x="-6.738" y="0" dx="1.475" dy="0.2" layer="1"/>
<smd name="14" x="-6.738" y="-0.4" dx="1.475" dy="0.2" layer="1"/>
<smd name="15" x="-6.738" y="-0.8" dx="1.475" dy="0.2" layer="1"/>
<smd name="16" x="-6.738" y="-1.2" dx="1.475" dy="0.2" layer="1"/>
<smd name="17" x="-6.738" y="-1.6" dx="1.475" dy="0.2" layer="1"/>
<smd name="18" x="-6.738" y="-2" dx="1.475" dy="0.2" layer="1"/>
<smd name="19" x="-6.738" y="-2.4" dx="1.475" dy="0.2" layer="1"/>
<smd name="20" x="-6.738" y="-2.8" dx="1.475" dy="0.2" layer="1"/>
<smd name="21" x="-6.738" y="-3.2" dx="1.475" dy="0.2" layer="1"/>
<smd name="22" x="-6.738" y="-3.6" dx="1.475" dy="0.2" layer="1"/>
<smd name="23" x="-6.738" y="-4" dx="1.475" dy="0.2" layer="1"/>
<smd name="24" x="-6.738" y="-4.4" dx="1.475" dy="0.2" layer="1"/>
<smd name="25" x="-6.738" y="-4.8" dx="1.475" dy="0.2" layer="1"/>
<smd name="26" x="-4.8" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="27" x="-4.4" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="28" x="-4" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="29" x="-3.6" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="30" x="-3.2" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="31" x="-2.8" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="32" x="-2.4" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="33" x="-2" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="34" x="-1.6" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="35" x="-1.2" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="36" x="-0.8" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="37" x="-0.4" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="38" x="0" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="39" x="0.4" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="40" x="0.8" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="41" x="1.2" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="42" x="1.6" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="43" x="2" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="44" x="2.4" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="45" x="2.8" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="46" x="3.2" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="47" x="3.6" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="48" x="4" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="49" x="4.4" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="50" x="4.8" y="-6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="51" x="6.738" y="-4.8" dx="1.475" dy="0.2" layer="1"/>
<smd name="52" x="6.738" y="-4.4" dx="1.475" dy="0.2" layer="1"/>
<smd name="53" x="6.738" y="-4" dx="1.475" dy="0.2" layer="1"/>
<smd name="54" x="6.738" y="-3.6" dx="1.475" dy="0.2" layer="1"/>
<smd name="55" x="6.738" y="-3.2" dx="1.475" dy="0.2" layer="1"/>
<smd name="56" x="6.738" y="-2.8" dx="1.475" dy="0.2" layer="1"/>
<smd name="57" x="6.738" y="-2.4" dx="1.475" dy="0.2" layer="1"/>
<smd name="58" x="6.738" y="-2" dx="1.475" dy="0.2" layer="1"/>
<smd name="59" x="6.738" y="-1.6" dx="1.475" dy="0.2" layer="1"/>
<smd name="60" x="6.738" y="-1.2" dx="1.475" dy="0.2" layer="1"/>
<smd name="61" x="6.738" y="-0.8" dx="1.475" dy="0.2" layer="1"/>
<smd name="62" x="6.738" y="-0.4" dx="1.475" dy="0.2" layer="1"/>
<smd name="63" x="6.738" y="0" dx="1.475" dy="0.2" layer="1"/>
<smd name="64" x="6.738" y="0.4" dx="1.475" dy="0.2" layer="1"/>
<smd name="65" x="6.738" y="0.8" dx="1.475" dy="0.2" layer="1"/>
<smd name="66" x="6.738" y="1.2" dx="1.475" dy="0.2" layer="1"/>
<smd name="67" x="6.738" y="1.6" dx="1.475" dy="0.2" layer="1"/>
<smd name="68" x="6.738" y="2" dx="1.475" dy="0.2" layer="1"/>
<smd name="69" x="6.738" y="2.4" dx="1.475" dy="0.2" layer="1"/>
<smd name="70" x="6.738" y="2.8" dx="1.475" dy="0.2" layer="1"/>
<smd name="71" x="6.738" y="3.2" dx="1.475" dy="0.2" layer="1"/>
<smd name="72" x="6.738" y="3.6" dx="1.475" dy="0.2" layer="1"/>
<smd name="73" x="6.738" y="4" dx="1.475" dy="0.2" layer="1"/>
<smd name="74" x="6.738" y="4.4" dx="1.475" dy="0.2" layer="1"/>
<smd name="75" x="6.738" y="4.8" dx="1.475" dy="0.2" layer="1"/>
<smd name="76" x="4.8" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="77" x="4.4" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="78" x="4" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="79" x="3.6" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="80" x="3.2" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="81" x="2.8" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="82" x="2.4" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="83" x="2" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="84" x="1.6" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="85" x="1.2" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="86" x="0.8" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="87" x="0.4" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="88" x="0" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="89" x="-0.4" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="90" x="-0.8" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="91" x="-1.2" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="92" x="-1.6" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="93" x="-2" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="94" x="-2.4" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="95" x="-2.8" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="96" x="-3.2" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="97" x="-3.6" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="98" x="-4" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="99" x="-4.4" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<smd name="100" x="-4.8" y="6.738" dx="1.475" dy="0.2" layer="1" rot="R90"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-7.725" y1="7.725" x2="7.725" y2="7.725" width="0.05" layer="51"/>
<wire x1="7.725" y1="7.725" x2="7.725" y2="-7.725" width="0.05" layer="51"/>
<wire x1="7.725" y1="-7.725" x2="-7.725" y2="-7.725" width="0.05" layer="51"/>
<wire x1="-7.725" y1="-7.725" x2="-7.725" y2="7.725" width="0.05" layer="51"/>
<wire x1="-6" y1="6" x2="6" y2="6" width="0.1" layer="51"/>
<wire x1="6" y1="6" x2="6" y2="-6" width="0.1" layer="51"/>
<wire x1="6" y1="-6" x2="-6" y2="-6" width="0.1" layer="51"/>
<wire x1="-6" y1="-6" x2="-6" y2="6" width="0.1" layer="51"/>
<wire x1="-6" y1="5.6" x2="-5.6" y2="6" width="0.1" layer="51"/>
<wire x1="-5.65" y1="5.65" x2="5.65" y2="5.65" width="0.2" layer="21"/>
<wire x1="5.65" y1="5.65" x2="5.65" y2="-5.65" width="0.2" layer="21"/>
<wire x1="5.65" y1="-5.65" x2="-5.65" y2="-5.65" width="0.2" layer="21"/>
<wire x1="-5.65" y1="-5.65" x2="-5.65" y2="5.65" width="0.2" layer="21"/>
<circle x="-7.275" y="5.4" radius="0.1" width="0.2" layer="25"/>
</package>
</packages>
<symbols>
<symbol name="PIC32MK1024MCF100-I_PT">
<wire x1="5.08" y1="53.34" x2="142.24" y2="53.34" width="0.254" layer="94"/>
<wire x1="142.24" y1="-129.54" x2="142.24" y2="53.34" width="0.254" layer="94"/>
<wire x1="142.24" y1="-129.54" x2="5.08" y2="-129.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="53.34" x2="5.08" y2="-129.54" width="0.254" layer="94"/>
<text x="143.51" y="58.42" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="143.51" y="55.88" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="AN23/CVD23/PMPA23/RG15" x="0" y="0" length="middle"/>
<pin name="VDD_1" x="0" y="-2.54" length="middle"/>
<pin name="TCK/RPA7/PWM10H/PWM4L/PMPD5/RA7" x="0" y="-5.08" length="middle"/>
<pin name="RPB14/PWM1H/VBUSON1/PMPD6/RB14" x="0" y="-7.62" length="middle"/>
<pin name="RPB15/PWM7H/PWM1L/PMPD7/RB15" x="0" y="-10.16" length="middle"/>
<pin name="PWM11H/PWM5L/RD1" x="0" y="-12.7" length="middle"/>
<pin name="PWM5H/RD2" x="0" y="-15.24" length="middle"/>
<pin name="RPD3/PWM12H/PWM6L/RD3" x="0" y="-17.78" length="middle"/>
<pin name="RPD4/PWM6H/RD4" x="0" y="-20.32" length="middle"/>
<pin name="AN19/CVD19/RPG6/VBUSON2/PMPA5/RG6" x="0" y="-22.86" length="middle"/>
<pin name="AN18/CVD18/RPG7/PMPA4/RG7(5)" x="0" y="-25.4" length="middle"/>
<pin name="AN17/CVD17/RPG8/PMPA3/RG8(6)" x="0" y="-27.94" length="middle"/>
<pin name="!MCLR" x="0" y="-30.48" length="middle"/>
<pin name="AN16/CVD16/RPG9/PMPA2/RG9" x="0" y="-33.02" length="middle"/>
<pin name="VSS_1" x="0" y="-35.56" length="middle"/>
<pin name="VDD_2" x="0" y="-38.1" length="middle"/>
<pin name="AN22/CVD22/RG10" x="0" y="-40.64" length="middle"/>
<pin name="AN21/CVD21/RE8" x="0" y="-43.18" length="middle"/>
<pin name="AN20/CVD20/RE9" x="0" y="-45.72" length="middle"/>
<pin name="AN10/CVD10/RPA12/USBOEN2/RA12" x="0" y="-48.26" length="middle"/>
<pin name="AN9/CVD9/RPA11/USBOEN1/RA11" x="0" y="-50.8" length="middle"/>
<pin name="OA2OUT/AN0/C2IN4-/C4IN3-/RPA0/RA0" x="0" y="-53.34" length="middle"/>
<pin name="OA2IN+/AN1/C2IN1+/RPA1/RA1" x="0" y="-55.88" length="middle"/>
<pin name="PGED3/OA2IN-/AN2/C2IN1-/RPB0/CTED2/RB0" x="0" y="-58.42" length="middle"/>
<pin name="PGEC3/OA1OUT/AN3/C1IN4-/C4IN2-/RPB1/CTED1/RB1" x="0" y="-60.96" length="middle"/>
<pin name="PGEC1/OA1IN+/AN4/C1IN1+/C1IN3-/C2IN3-/RPB2/RB2" x="43.18" y="-134.62" length="middle" rot="R90"/>
<pin name="PGED1/OA1IN-/AN5/CTCMP/C1IN1-/RTCC/RPB3/RB3" x="45.72" y="-134.62" length="middle" rot="R90"/>
<pin name="VREF-/AN33/CVD33/PMPA7/RF9" x="48.26" y="-134.62" length="middle" rot="R90"/>
<pin name="VREF+/AN34/CVD34/PMPA6/RF10" x="50.8" y="-134.62" length="middle" rot="R90"/>
<pin name="AVDD" x="53.34" y="-134.62" length="middle" rot="R90"/>
<pin name="AVSS" x="55.88" y="-134.62" length="middle" rot="R90"/>
<pin name="OA3OUT/AN6/CVD6/C3IN4-/C4IN1+/C4IN4-/RPC0/RC0" x="58.42" y="-134.62" length="middle" rot="R90"/>
<pin name="OA3IN-/AN7/CVD7/C3IN1-/C4IN1-/RPC1/RC1" x="60.96" y="-134.62" length="middle" rot="R90"/>
<pin name="OA3IN+/AN8/CVD8/C3IN1+/C3IN3-/RPC2/FLT3/PMPA13/RC2" x="63.5" y="-134.62" length="middle" rot="R90"/>
<pin name="AN11/CVD11/C1IN2-/FLT4/PMPA12/RC11" x="66.04" y="-134.62" length="middle" rot="R90"/>
<pin name="VSS_2" x="68.58" y="-134.62" length="middle" rot="R90"/>
<pin name="VDD_3" x="71.12" y="-134.62" length="middle" rot="R90"/>
<pin name="AN35/CVD35/RG11" x="73.66" y="-134.62" length="middle" rot="R90"/>
<pin name="AN36/CVD36/RF13" x="76.2" y="-134.62" length="middle" rot="R90"/>
<pin name="AN37/CVD37/RF12" x="78.74" y="-134.62" length="middle" rot="R90"/>
<pin name="AN12/CVD12/C2IN2-/C5IN2-/FLT5/PMPA11/RE12(6)" x="81.28" y="-134.62" length="middle" rot="R90"/>
<pin name="AN13/CVD13/C3IN2-/FLT6/PMPA10/RE13(5)" x="83.82" y="-134.62" length="middle" rot="R90"/>
<pin name="AN14/CVD14/RPE14/FLT7/PMPA1/PSPA1/RE14" x="86.36" y="-134.62" length="middle" rot="R90"/>
<pin name="AN15/CVD15/RPE15/FLT8/PMPA0/PSPA0/RE15" x="88.9" y="-134.62" length="middle" rot="R90"/>
<pin name="VSS_3" x="91.44" y="-134.62" length="middle" rot="R90"/>
<pin name="VDD_4" x="93.98" y="-134.62" length="middle" rot="R90"/>
<pin name="AN38/CVD38/RD14" x="96.52" y="-134.62" length="middle" rot="R90"/>
<pin name="AN39/CVD39/RD15" x="99.06" y="-134.62" length="middle" rot="R90"/>
<pin name="TDI/DAC3/AN26/CVD26/RPA8/PMPA9/RA8(6)" x="101.6" y="-134.62" length="middle" rot="R90"/>
<pin name="FLT15/RPB4/PMPA8/RB4(5)" x="104.14" y="-134.62" length="middle" rot="R90"/>
<pin name="VSS_5" x="147.32" y="0" length="middle" rot="R180"/>
<pin name="SOSCO/RPB8(4)/RB8(4)" x="147.32" y="-2.54" length="middle" rot="R180"/>
<pin name="SOSCI/RPC13(4)/RC13(4)" x="147.32" y="-5.08" length="middle" rot="R180"/>
<pin name="OA5OUT/AN25/CVD25/C5IN4-/RPB7/SCK1/INT0/RB7" x="147.32" y="-7.62" length="middle" rot="R180"/>
<pin name="DAC2/AN48/CVD48/RPC10/PMPA14/PSPCS/RC10" x="147.32" y="-10.16" length="middle" rot="R180"/>
<pin name="PGEC2/RPB6/SCK2/PMPA15/RB6(5)" x="147.32" y="-12.7" length="middle" rot="R180"/>
<pin name="PGED2/RPB5/USBID1/RB5(6)" x="147.32" y="-15.24" length="middle" rot="R180"/>
<pin name="RD8" x="147.32" y="-17.78" length="middle" rot="R180"/>
<pin name="AN47/CVD47/RPA15/RA15" x="147.32" y="-20.32" length="middle" rot="R180"/>
<pin name="AN46/CVD46/RPA14/RA14" x="147.32" y="-22.86" length="middle" rot="R180"/>
<pin name="VSS_4" x="147.32" y="-25.4" length="middle" rot="R180"/>
<pin name="OSCO/CLKO/RPC15/RC15" x="147.32" y="-27.94" length="middle" rot="R180"/>
<pin name="OSCI/CLKI/AN49/CVD49/RPC12/RC12" x="147.32" y="-30.48" length="middle" rot="R180"/>
<pin name="VDD_5" x="147.32" y="-33.02" length="middle" rot="R180"/>
<pin name="AN45/CVD45/RF5" x="147.32" y="-35.56" length="middle" rot="R180"/>
<pin name="D2+" x="147.32" y="-38.1" length="middle" rot="R180"/>
<pin name="D2-" x="147.32" y="-40.64" length="middle" rot="R180"/>
<pin name="VBUS2" x="147.32" y="-43.18" length="middle" rot="R180"/>
<pin name="D1+" x="147.32" y="-45.72" length="middle" rot="R180"/>
<pin name="D1-" x="147.32" y="-48.26" length="middle" rot="R180"/>
<pin name="VUSB3V3" x="147.32" y="-50.8" length="middle" rot="R180"/>
<pin name="VBUS" x="147.32" y="-53.34" length="middle" rot="R180"/>
<pin name="AN41/CVD41/RPE1/RE1" x="147.32" y="-55.88" length="middle" rot="R180"/>
<pin name="AN40/CVD40/RPE0/RE0" x="147.32" y="-58.42" length="middle" rot="R180"/>
<pin name="OA5IN+/DAC1/AN24/CVD24/C5IN1+/C5IN3-/RPA4/T1CK/T1G/_RA4" x="147.32" y="-60.96" length="middle" rot="R180"/>
<pin name="TDO/PWM4H/PMPD4/RA10" x="43.18" y="58.42" length="middle" rot="R270"/>
<pin name="RPB13/PWM8H/PWM2L/CTPLS/PMPD3/RB13" x="45.72" y="58.42" length="middle" rot="R270"/>
<pin name="RPB12/PWM2H/PMPD2/RB12" x="48.26" y="58.42" length="middle" rot="R270"/>
<pin name="TRD0/PMPA22/RG13" x="50.8" y="58.42" length="middle" rot="R270"/>
<pin name="TRD1/RPG12/PMPA21/RG12" x="53.34" y="58.42" length="middle" rot="R270"/>
<pin name="TRD2/PMPA20/RG14" x="55.88" y="58.42" length="middle" rot="R270"/>
<pin name="RPB11/PWM9H/PWM3L/PMPD1/RB11" x="58.42" y="58.42" length="middle" rot="R270"/>
<pin name="RPB10/PWM3H/PMPD0/RB10" x="60.96" y="58.42" length="middle" rot="R270"/>
<pin name="TRD3/PMPA19/RF7" x="63.5" y="58.42" length="middle" rot="R270"/>
<pin name="TRCLK/PMPA18/RF6" x="66.04" y="58.42" length="middle" rot="R270"/>
<pin name="RPG0/PMPD8/RG0" x="68.58" y="58.42" length="middle" rot="R270"/>
<pin name="RPG1/PMPD9/RG1" x="71.12" y="58.42" length="middle" rot="R270"/>
<pin name="RPF1/PWM11L/PMPD10/RF1" x="73.66" y="58.42" length="middle" rot="R270"/>
<pin name="RPF0/PWM11H/PMPD11/RF0" x="76.2" y="58.42" length="middle" rot="R270"/>
<pin name="VDD_6" x="78.74" y="58.42" length="middle" rot="R270"/>
<pin name="VSS_6" x="81.28" y="58.42" length="middle" rot="R270"/>
<pin name="RPC9/PMPD15/RC9" x="83.82" y="58.42" length="middle" rot="R270"/>
<pin name="RPD6/PWM12L/PMPD14/RD6" x="86.36" y="58.42" length="middle" rot="R270"/>
<pin name="RPD5/PWM12H/PMPRD/PSPRD/RD5" x="88.9" y="58.42" length="middle" rot="R270"/>
<pin name="RPC8/PMPWR/PSPWR/RC8" x="91.44" y="58.42" length="middle" rot="R270"/>
<pin name="PMPD13/RD13" x="93.98" y="58.42" length="middle" rot="R270"/>
<pin name="PMPD12/RD12" x="96.52" y="58.42" length="middle" rot="R270"/>
<pin name="RPC7/PMPA17/RC7" x="99.06" y="58.42" length="middle" rot="R270"/>
<pin name="RPC6/USBID2/PMPA16/RC6" x="101.6" y="58.42" length="middle" rot="R270"/>
<pin name="TMS/OA5IN-/AN27/CVD27/C5IN1-/RPB9/RB9" x="104.14" y="58.42" length="middle" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="PIC32MK1024MCF100-I_PT" prefix="IC">
<description>&lt;b&gt;Microchip Technology MCU32, 120MHz, 4 I2C, 6 I2S, USB FS, CAN 2.0B, 12-bit ADC, Motor Control&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="http://ww1.microchip.com/downloads/en/DeviceDoc/60001402D.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="PIC32MK1024MCF100-I_PT" x="0" y="0"/>
</gates>
<devices>
<device name="" package="QFP40P1400X1400X120-100N">
<connects>
<connect gate="G$1" pin="!MCLR" pad="13"/>
<connect gate="G$1" pin="AN10/CVD10/RPA12/USBOEN2/RA12" pad="20"/>
<connect gate="G$1" pin="AN11/CVD11/C1IN2-/FLT4/PMPA12/RC11" pad="35"/>
<connect gate="G$1" pin="AN12/CVD12/C2IN2-/C5IN2-/FLT5/PMPA11/RE12(6)" pad="41"/>
<connect gate="G$1" pin="AN13/CVD13/C3IN2-/FLT6/PMPA10/RE13(5)" pad="42"/>
<connect gate="G$1" pin="AN14/CVD14/RPE14/FLT7/PMPA1/PSPA1/RE14" pad="43"/>
<connect gate="G$1" pin="AN15/CVD15/RPE15/FLT8/PMPA0/PSPA0/RE15" pad="44"/>
<connect gate="G$1" pin="AN16/CVD16/RPG9/PMPA2/RG9" pad="14"/>
<connect gate="G$1" pin="AN17/CVD17/RPG8/PMPA3/RG8(6)" pad="12"/>
<connect gate="G$1" pin="AN18/CVD18/RPG7/PMPA4/RG7(5)" pad="11"/>
<connect gate="G$1" pin="AN19/CVD19/RPG6/VBUSON2/PMPA5/RG6" pad="10"/>
<connect gate="G$1" pin="AN20/CVD20/RE9" pad="19"/>
<connect gate="G$1" pin="AN21/CVD21/RE8" pad="18"/>
<connect gate="G$1" pin="AN22/CVD22/RG10" pad="17"/>
<connect gate="G$1" pin="AN23/CVD23/PMPA23/RG15" pad="1"/>
<connect gate="G$1" pin="AN35/CVD35/RG11" pad="38"/>
<connect gate="G$1" pin="AN36/CVD36/RF13" pad="39"/>
<connect gate="G$1" pin="AN37/CVD37/RF12" pad="40"/>
<connect gate="G$1" pin="AN38/CVD38/RD14" pad="47"/>
<connect gate="G$1" pin="AN39/CVD39/RD15" pad="48"/>
<connect gate="G$1" pin="AN40/CVD40/RPE0/RE0" pad="52"/>
<connect gate="G$1" pin="AN41/CVD41/RPE1/RE1" pad="53"/>
<connect gate="G$1" pin="AN45/CVD45/RF5" pad="61"/>
<connect gate="G$1" pin="AN46/CVD46/RPA14/RA14" pad="66"/>
<connect gate="G$1" pin="AN47/CVD47/RPA15/RA15" pad="67"/>
<connect gate="G$1" pin="AN9/CVD9/RPA11/USBOEN1/RA11" pad="21"/>
<connect gate="G$1" pin="AVDD" pad="30"/>
<connect gate="G$1" pin="AVSS" pad="31"/>
<connect gate="G$1" pin="D1+" pad="57"/>
<connect gate="G$1" pin="D1-" pad="56"/>
<connect gate="G$1" pin="D2+" pad="60"/>
<connect gate="G$1" pin="D2-" pad="59"/>
<connect gate="G$1" pin="DAC2/AN48/CVD48/RPC10/PMPA14/PSPCS/RC10" pad="71"/>
<connect gate="G$1" pin="FLT15/RPB4/PMPA8/RB4(5)" pad="50"/>
<connect gate="G$1" pin="OA2IN+/AN1/C2IN1+/RPA1/RA1" pad="23"/>
<connect gate="G$1" pin="OA2OUT/AN0/C2IN4-/C4IN3-/RPA0/RA0" pad="22"/>
<connect gate="G$1" pin="OA3IN+/AN8/CVD8/C3IN1+/C3IN3-/RPC2/FLT3/PMPA13/RC2" pad="34"/>
<connect gate="G$1" pin="OA3IN-/AN7/CVD7/C3IN1-/C4IN1-/RPC1/RC1" pad="33"/>
<connect gate="G$1" pin="OA3OUT/AN6/CVD6/C3IN4-/C4IN1+/C4IN4-/RPC0/RC0" pad="32"/>
<connect gate="G$1" pin="OA5IN+/DAC1/AN24/CVD24/C5IN1+/C5IN3-/RPA4/T1CK/T1G/_RA4" pad="51"/>
<connect gate="G$1" pin="OA5OUT/AN25/CVD25/C5IN4-/RPB7/SCK1/INT0/RB7" pad="72"/>
<connect gate="G$1" pin="OSCI/CLKI/AN49/CVD49/RPC12/RC12" pad="63"/>
<connect gate="G$1" pin="OSCO/CLKO/RPC15/RC15" pad="64"/>
<connect gate="G$1" pin="PGEC1/OA1IN+/AN4/C1IN1+/C1IN3-/C2IN3-/RPB2/RB2" pad="26"/>
<connect gate="G$1" pin="PGEC2/RPB6/SCK2/PMPA15/RB6(5)" pad="70"/>
<connect gate="G$1" pin="PGEC3/OA1OUT/AN3/C1IN4-/C4IN2-/RPB1/CTED1/RB1" pad="25"/>
<connect gate="G$1" pin="PGED1/OA1IN-/AN5/CTCMP/C1IN1-/RTCC/RPB3/RB3" pad="27"/>
<connect gate="G$1" pin="PGED2/RPB5/USBID1/RB5(6)" pad="69"/>
<connect gate="G$1" pin="PGED3/OA2IN-/AN2/C2IN1-/RPB0/CTED2/RB0" pad="24"/>
<connect gate="G$1" pin="PMPD12/RD12" pad="79"/>
<connect gate="G$1" pin="PMPD13/RD13" pad="80"/>
<connect gate="G$1" pin="PWM11H/PWM5L/RD1" pad="6"/>
<connect gate="G$1" pin="PWM5H/RD2" pad="7"/>
<connect gate="G$1" pin="RD8" pad="68"/>
<connect gate="G$1" pin="RPB10/PWM3H/PMPD0/RB10" pad="93"/>
<connect gate="G$1" pin="RPB11/PWM9H/PWM3L/PMPD1/RB11" pad="94"/>
<connect gate="G$1" pin="RPB12/PWM2H/PMPD2/RB12" pad="98"/>
<connect gate="G$1" pin="RPB13/PWM8H/PWM2L/CTPLS/PMPD3/RB13" pad="99"/>
<connect gate="G$1" pin="RPB14/PWM1H/VBUSON1/PMPD6/RB14" pad="4"/>
<connect gate="G$1" pin="RPB15/PWM7H/PWM1L/PMPD7/RB15" pad="5"/>
<connect gate="G$1" pin="RPC6/USBID2/PMPA16/RC6" pad="77"/>
<connect gate="G$1" pin="RPC7/PMPA17/RC7" pad="78"/>
<connect gate="G$1" pin="RPC8/PMPWR/PSPWR/RC8" pad="81"/>
<connect gate="G$1" pin="RPC9/PMPD15/RC9" pad="84"/>
<connect gate="G$1" pin="RPD3/PWM12H/PWM6L/RD3" pad="8"/>
<connect gate="G$1" pin="RPD4/PWM6H/RD4" pad="9"/>
<connect gate="G$1" pin="RPD5/PWM12H/PMPRD/PSPRD/RD5" pad="82"/>
<connect gate="G$1" pin="RPD6/PWM12L/PMPD14/RD6" pad="83"/>
<connect gate="G$1" pin="RPF0/PWM11H/PMPD11/RF0" pad="87"/>
<connect gate="G$1" pin="RPF1/PWM11L/PMPD10/RF1" pad="88"/>
<connect gate="G$1" pin="RPG0/PMPD8/RG0" pad="90"/>
<connect gate="G$1" pin="RPG1/PMPD9/RG1" pad="89"/>
<connect gate="G$1" pin="SOSCI/RPC13(4)/RC13(4)" pad="73"/>
<connect gate="G$1" pin="SOSCO/RPB8(4)/RB8(4)" pad="74"/>
<connect gate="G$1" pin="TCK/RPA7/PWM10H/PWM4L/PMPD5/RA7" pad="3"/>
<connect gate="G$1" pin="TDI/DAC3/AN26/CVD26/RPA8/PMPA9/RA8(6)" pad="49"/>
<connect gate="G$1" pin="TDO/PWM4H/PMPD4/RA10" pad="100"/>
<connect gate="G$1" pin="TMS/OA5IN-/AN27/CVD27/C5IN1-/RPB9/RB9" pad="76"/>
<connect gate="G$1" pin="TRCLK/PMPA18/RF6" pad="91"/>
<connect gate="G$1" pin="TRD0/PMPA22/RG13" pad="97"/>
<connect gate="G$1" pin="TRD1/RPG12/PMPA21/RG12" pad="96"/>
<connect gate="G$1" pin="TRD2/PMPA20/RG14" pad="95"/>
<connect gate="G$1" pin="TRD3/PMPA19/RF7" pad="92"/>
<connect gate="G$1" pin="VBUS" pad="54"/>
<connect gate="G$1" pin="VBUS2" pad="58"/>
<connect gate="G$1" pin="VDD_1" pad="2"/>
<connect gate="G$1" pin="VDD_2" pad="16"/>
<connect gate="G$1" pin="VDD_3" pad="37"/>
<connect gate="G$1" pin="VDD_4" pad="46"/>
<connect gate="G$1" pin="VDD_5" pad="62"/>
<connect gate="G$1" pin="VDD_6" pad="86"/>
<connect gate="G$1" pin="VREF+/AN34/CVD34/PMPA6/RF10" pad="29"/>
<connect gate="G$1" pin="VREF-/AN33/CVD33/PMPA7/RF9" pad="28"/>
<connect gate="G$1" pin="VSS_1" pad="15"/>
<connect gate="G$1" pin="VSS_2" pad="36"/>
<connect gate="G$1" pin="VSS_3" pad="45"/>
<connect gate="G$1" pin="VSS_4" pad="65"/>
<connect gate="G$1" pin="VSS_5" pad="75"/>
<connect gate="G$1" pin="VSS_6" pad="85"/>
<connect gate="G$1" pin="VUSB3V3" pad="55"/>
</connects>
<technologies>
<technology name="">
<attribute name="DESCRIPTION" value="Microchip Technology MCU32, 120MHz, 4 I2C, 6 I2S, USB FS, CAN 2.0B, 12-bit ADC, Motor Control" constant="no"/>
<attribute name="HEIGHT" value="1.2mm" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Microchip" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="PIC32MK1024MCF100-I/PT" constant="no"/>
<attribute name="MOUSER_PART_NUMBER" value="579-2MK1024MCF100IPT" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.com/Search/Refine.aspx?Keyword=579-2MK1024MCF100IPT" constant="no"/>
<attribute name="RS_PART_NUMBER" value="1449608P" constant="no"/>
<attribute name="RS_PRICE-STOCK" value="http://uk.rs-online.com/web/p/products/1449608P" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="IC1" library="PIC32MK1024MCF100-I_PT" deviceset="PIC32MK1024MCF100-I_PT" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="IC1" gate="G$1" x="12.7" y="45.72" smashed="yes">
<attribute name="NAME" x="156.21" y="104.14" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="156.21" y="101.6" size="1.778" layer="96" align="center-left"/>
</instance>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
