
# ����л�����
## �ҵ����
	�趨��������������ೡ���������ȶ���崻���������Ͽ����������ǡ�ȫ�����������
## center player
	state: 
		Playing,
				//enter:����ת�� ��Ϣ. ����zoneId
				//���� Ԥ����ת��Ŀ��zone.						--ReqZoneReserve
				//���� ��ӦԤ����ת��Դzone, �ɹ�Ԥ������ Moving��--RspZoneReserve

		Moving, //enter:���� send to zone��Ϣ
				//�յ�zone ת�� zone�� ת��Ŀ��zone ������Playing	--ReqTranZone

## zone Player
	state: 
		None   : //���� ReqZoneReserve,�ɹ�����WaitTranIn��ʧ��֪ͨcenter --RspZoneReserve
				
		Playing: 
				//����acc ���棬���� center Ԥ��λ��,����WaitReserve��		--MsgReqCacheMsg�� ReqZoneReserve

		WaitTranIn:  //���� ReqTranZone�� ����acc�ָ�,����acc ����, ����Playing.  --MsgReqCacheMsg


		WaitReserve: (��ֹ�ظ�����Ԥ��)
				// ������Ӧ acc����, center Ԥ����ok�� ���� ת��zone. ɾ���Լ��� --RspZoneReserve��MsgRspCacheMsg��ReqTranZone
					(��֤ ɾ���󣬲����յ� Player ��ҵ������)
				//����center Ԥ��ʧ�ܣ�����Playing.				--RspZoneReserve

#��¼����
## center player
	state:
		None:
			�����¼����db,����player. ����WaitLogin

		WaitLogin:
			�����¼���ܾ���
			����zone ��¼player.							--ReqLoginZone_sc
			���� zone ��¼player �ɹ��� ���� LoginOk		--RspLoginZone_cs

		LoginOk: ��������������״̬
			�����ص�¼������zone �ص�¼�� ���� WaitReLogin	--ReqReLoginZone_sc

		WaitReLogin: 
			���� zone �ص�¼player �ɹ��� ���� LoginOk		--RspReLoginZone_cs
			
## zone Player
	state: 
		None   : 
				���� ��¼������ player������LoginOk  --ReqLoginZone_sc RspLoginZone_cs

		LoginOk:
				���� �ص�¼���滻session 	--ReqReLoginZone_sc RspReLoginZone_cs
				�� session ɾ�������� OffLine

		OffLine:
				���� ��¼������LoginOk  --ReqLoginZone_sc RspLoginZone_cs
				���߳�ʱ��del player.