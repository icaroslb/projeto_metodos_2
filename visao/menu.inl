#include "menu.h"

void menus (int &tipo) {
   ImGui::GetStyle().WindowRounding = 0.0f;
   
    switch (tipo){
    case MENU:
    	menuPrincipal(tipo);
    break;
    case DERIVADA:
    break;
    case INTEGRAL:
      menuIntegral();
    break;
    case AUTO:
      
    break;
    }
   
   if(mostrarSobreMenu){
      sobreMenu();
   }
}

void menuPrincipal (int &tipo) {
	ImVec2 tamanho((ImGui::GetIO().DisplaySize.x*3.0)/4.0, ((ImGui::GetIO().DisplaySize.y)*5.0)/6.0);
	
	ImGui::SetWindowSize("Botoes", tamanho);
	ImGui::SetNextWindowPosCenter();

	ImGui::Begin("Botoes", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		ImVec2 tamBotoes((tamanho.x*3.0)/4.0, tamanho.y/5.0);
		float distancia = (tamanho.x/2) - (tamBotoes.x/2);

		ImGui::SameLine(distancia);
		if(ImGui::Button("Derivada", tamBotoes)) { tipo = DERIVADA; }

		ImGui::NewLine();
		ImGui::SameLine(distancia);
		if(ImGui::Button("Integral", tamBotoes)) { tipo = INTEGRAL; }

		ImGui::NewLine();
		ImGui::SameLine(distancia);
		if(ImGui::Button("Autovetor e Autovalor", tamBotoes)) { tipo = AUTO; }

		ImGui::NewLine();
		ImGui::SameLine(distancia);
		if(ImGui::Button("Problema do valor inicial", tamBotoes)) { }

		ImGui::NewLine();
		ImGui::SameLine(distancia);
		if(ImGui::Button("Problema de valor de contorno", tamBotoes)) { }
	ImGui::End();

   ImGui::BeginMainMenuBar();
		if(ImGui::BeginMenu("Arquivo")){
			if(ImGui::MenuItem("Derivada"))                  { tipo = DERIVADA; }
			if(ImGui::MenuItem("Integral"))                  { tipo = INTEGRAL; }
			if(ImGui::MenuItem("Autovetores e autovalores")) { tipo = AUTO; }
			ImGui::MenuItem("Sair");
			
			ImGui::EndMenu();
		}
		
		if(ImGui::BeginMenu("Ajuda")){
			mostrarSobreMenu |= ImGui::MenuItem("Sobre");
			
			ImGui::EndMenu();
		}
	ImGui::EndMainMenuBar();
}

void sobreMenu () {
	ImVec2 tamanho(200, 100), posicao((ImGui::GetWindowWidth()), (ImGui::GetWindowHeight()));
	
	ImGui::SetWindowSize("Sobre", tamanho);
	ImGui::SetNextWindowPosCenter();
    ImGui::Begin("Sobre", &mostrarSobreMenu, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
		ImGui::PushTextWrapPos(200);
    	ImGui::Text("Métodos Numéricos 2");
		ImGui::Separator();
		ImGui::AlignFirstTextHeightToWidgets();
		ImGui::Text("Programa de métodos numéricos criado para a cadeira de métodos 2");
		ImGui::PopTextWrapPos();
    ImGui::End();
}

void menuIntegral () {
	static char novaExpressao[30], *item[] = {"", "Newton Cotes", "Gauss Legendre", "Exponencial"};
	ImVec2 tamanho(250, 170);
	static int qtd = 0, val = 0;
	static bool func = false, area = false, interpolacao = false; 
	static std::string resposta;
	
	funcaoInterpoladoraNewton();

	if(area){
		mostrarArea(valInterpol, interpol);
	}
	if(func){
		mostrarFuncao(inter);
	}
	if(interpolacao){
		mostrarInterpolacao(valInterpol, interpol, pontosInterpol, valPontosInterpol);
	}

	ImGui::SetWindowSize("Integral", tamanho);
	ImGui::Begin("Integral", NULL, ImGuiWindowFlags_NoResize);
		ImGui::Checkbox("Função", &func);
		ImGui::SameLine();
		ImGui::Checkbox("Área", &area);
		ImGui::SameLine();
		ImGui::Checkbox("Interpolação", &interpolacao);

		ImGui::InputText("Equação", novaExpressao, 30);
		ImGui::InputFloat2("Intervalo", inter);
		ImGui::Combo("Método", &qtd, item, IM_ARRAYSIZE(item));

		switch (qtd){
			case 1:
				ImGui::InputInt("Grau", &val);
			break;
			case 2:
				ImGui::InputInt("Nº pontos", &val);
			break;
			case 3:

			break;
		}

		if(ImGui::Button("Calcular")){
			if(textoExpre.compare(novaExpressao) != 0){
				textoExpre = novaExpressao;

				expressao = parser(textoExpre);
			}
		}
		ImGui::SameLine();
		ImGui::Text(resposta.data());

	ImGui::End();
}

void funcaoInterpoladoraNewton () {
	float dist = (inter[1] - inter[0]) / 3,
	      s, s2, s3, fim = inter[1] + QTD_DIST_UM;

				pontosInterpol.clear();
				valPontosInterpol.clear();

				pontosInterpol.push_back(inter[0]);
				pontosInterpol.push_back(pontosInterpol[0] + dist);
				pontosInterpol.push_back(pontosInterpol[1] + dist);
				pontosInterpol.push_back(inter[1]);

				valPontosInterpol.push_back(std::sin(pontosInterpol[0]));
				valPontosInterpol.push_back(std::sin(pontosInterpol[1]));
				valPontosInterpol.push_back(std::sin(pontosInterpol[2]));
				valPontosInterpol.push_back(std::sin(pontosInterpol[3]));

	valInterpol.clear();
	interpol.clear();

	for(float i = inter[0]; i <= fim; i += QTD_DIST_UM){
		s = (i - inter[0]) / dist;
		s2 = s * s;
		s3 = s2 * s;

		valInterpol.push_back(i);
		interpol.push_back(valPontosInterpol[0] +
		                   (s * (valPontosInterpol[1] - valPontosInterpol[0])) +
											 (((s2 - s) / 2.0) * (valPontosInterpol[2] - (2.0 * valPontosInterpol[1]) + valPontosInterpol[0])) +
											 (((s3 - (3.0 * s2) + (2.0 * s)) / 6.0) * (valPontosInterpol[3] - (3.0 * valPontosInterpol[2]) + (3.0 * valPontosInterpol[1]) - valPontosInterpol[0])));
	}
}