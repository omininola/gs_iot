# GS - Protech The Future | IoT

## Integrantes

| Nome                   |   RM   |
| :--------------------- | :----: |
| Otavio Miklos Nogueira | 554513 |
| Luciayla Yumi Kawakami | 557987 |

---

## Links

- Github: https://github.com/omininola/gs_iot
- Wokwi: https://wokwi.com/projects/433181212584749057
- ThingSpeak: https://thingspeak.mathworks.com/channels/2981469
- Apresentação: https://youtu.be/Or7rEASWQ_0
- Pitch: https://youtu.be/Sd4V2oEn3bM

---

## Descrição

Desenvolvemos um aplicativo mobile em React Native voltado para o relato e monitoramento de incêndios e queimadas. O sistema permite que usuários façam cadastro, login e publiquem relatórios de ocorrências, com possibilidade de filtrar por cidade ou visualizar apenas seus próprios relatos.

Além disso, o app conta com um dashboard em tempo real, alimentado por dados do ThingSpeak, onde gráficos mostram informações captadas por sensores embarcados em drones que sobrevoam áreas críticas. Esses drones são capazes de gerar relatórios automáticos, otimizando a identificação e resposta a desastres ambientais.

A aplicação consome uma REST API desenvolvida com Spring Boot, que se comunica com um banco de dados Oracle contendo tabelas interligadas como: Usuários, Relatórios, Drones, Sensores, Cidades, Estados e Países.

Combinando dados manuais e automáticos, o sistema visa acelerar a detecção de incêndios e fornecer informações valiosas para tomada de decisão por autoridades e cidadãos.

---

## Testes

Para testar o projeto, entre no link do Wokwi: https://wokwi.com/projects/433181212584749057
E rode o projeto, mexa nos valores dos sensores e veja eles sendo enviados em tempo real para o canal do ThingSpeak
ThingSpeak: https://thingspeak.mathworks.com/channels/2981469
