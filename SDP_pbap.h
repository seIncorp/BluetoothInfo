#pragma once

namespace SDP
{

	namespace PBAP
	{
		typedef enum
		{
			GoepL2capPsm = 0x0200,
			SupportedRepositories = 0x0314,
			PbapSupportedFeatures = 0x0317

		} ATTRIBUTE_ID_PBAP;

		struct SUPPORTED_REPOSITORIES_DATA_S
		{
			struct SR_S
			{
				BYTE a0 : 1;
				BYTE a1 : 1;
				BYTE a2 : 1;
				BYTE a3 : 1;
				BYTE : 4;
			};

			SR_S* repo;

			SUPPORTED_REPOSITORIES_DATA_S(BYTE* a) : repo((SR_S*)a)
			{
				printf("FROM STRUCT --> %X\n", *a);
			};

			std::string getSupportedRepositoriesString()
			{
				std::string temp = "";

				if (repo->a0)
				{
					temp += "Local Phonebook\n";
				}

				if (repo->a1)
				{
					temp += "SIM card\n";
				}

				if (repo->a2)
				{
					temp += "Speed dial\n";
				}

				if (repo->a3)
				{
					temp += "Favorites\n";
				}

				return temp;
			}
		};


		typedef struct SUPPORTED_REPOSITORIES_S : DEFAULT_OBJECT
		{
			struct VV : VALUE
			{
				SUPPORTED_REPOSITORIES_DATA_S* srs;

			} VALUE;

			template<class T>
			void print(T v)
			{
				printATTR_ELEMENT();

				printVALUE_ELEMENT(v);

				printf("Repositories: \n%s\n", v.srs->getSupportedRepositoriesString().c_str());
			}

		} SUPPORTED_REPOSITORIES, * PSUPPORTED_REPOSITORIES;

		typedef struct PBAP_SUPPORTED_FEATURES_S : DEFAULT_OBJECT
		{
			// TODO: print values
			template<class T>
			void print(T v)
			{
				printATTR_ELEMENT();

				printVALUE_ELEMENT(v);
			}


		} PBAP_SUPPORTED_FEATURES, * PPBAP_SUPPORTED_FEATURES;

		// GoepL2CapPsm use from MAP

		int getAndParse_SUPPORTED_REPOSITORIES_PBAP(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_PBAP_SUPPORTED_FEATURES_PBAP(ULONG recordHandle, HANDLE_SDP_TYPE aa);

	};


};