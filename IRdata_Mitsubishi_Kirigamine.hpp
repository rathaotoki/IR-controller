#ifndef IRdata_Mitsubishi_Kirigamine_H
#define IRdata_Mitsubishi_Kirigamine_H

#include "IRdata_AEHA.hpp"
#include "utils.h"

class Kirigamine : public IRdata_AEHA
{
	private:
		
	public:
		enum struct AirFlow
		{
			AUTO = 0,
			LOW,
			MIDDLE,
			HIGH
		};
		
		enum struct AirDirection
		{
			HIGHEST = 5,
			MIDDLE_UP = 10,
			MIDDLE = 11,
			MIDDLE_DOWN = 24,
			LOWEST = 13,
			MOVE = 15,
			AUTO = 16
		};
		
		enum struct Mode
		{
			WARM,
			DRY_WEAK,
			DRY_NORMAL,
			DRY_STRONG,
			COOL
		};
	
		Kirigamine();
		~Kirigamine(){}
	
		//純粋仮想関数の実装
		//基底クラスのGetData()で勝手に呼ばれるので明示的な呼び出しは不要
		void AppCalcParity();
		
		//プロダクト専用実装
		//リモコン：RH101416CL
		
		/*
			デフォルト設定
			
			28C, Cooler, 
			Airflow = auto
			AirDir = move
			power = off
			current weak = on
			powerfull mode = off
			timer off
			internal clean = on
		*/
		void setDefault();
			
		/*
			運転モードの設定
			COOL, DRY_WEAK/NORMAL/STRONG, WARM
		*/
		void setMode(Mode mode);
		
		/*
			電源設定
			true = on
		*/
		void setPowerState(bool on);
		
		/*
			温度設定
			セルシウス温度、16-31Cが設定範囲
		*/
		void setTemperature(int temp);
		
		/*
			風速設定
			AUTO, WEAK, MIDDLE, HIGH
		*/
		void setAirFlow(AirFlow mode);
		
		/*
			風向設定
			五段階+Move/Auto
		*/
		void setAirDirection(AirDirection mode);
		
		/*
			タイマー設定
			is_offTimer = trueで切タイマー
						= falseで入タイマー
			minutes=0でタイマー設定をoff
		*/
		void setTimer(bool is_offTimer, int minutes);
		
		/*
			内部クリーン
			flg=true でon
		*/
		void setInternalCleaning(bool flg);
		
		/*
			パワフルモード
			flg=trueでon
		*/
		void setPowerfullMode(bool flg);
		
		/*
			電流量設定
			flg=trueで低量設定
			falseだとノーマル
		*/
		void setCurrentWeak(bool flg);
		
};

#endif //IRdata_Mitsubishi_Kirigamine_H
