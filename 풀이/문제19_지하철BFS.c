/*=====================================================================
 * 문제 19. 지하철 노선 최단 환승 (그래프 BFS) - 풀이
 *  ※ 그래프는 라이브러리 범위(큐~정렬) 밖이라 인접 행렬을 직접 구현한다.
 *     단, BFS의 '방문 대기열'은 라이브러리 linkedQueue를 그대로 사용(조립).
 *  직접 구현: 인접 행렬 구성과 BFS 본체 (아래 자세히 주석)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "linkedQueue.h"

#define V 6   /* 역 개수 (0~5번 역) */

int main(void) {
	/* ── 직접 구현: 인접 행렬 ──
	   adj[i][j]=1 이면 i역과 j역이 직접 연결됨(무방향). */
	int adj[V][V] = { 0 };
	int edges[][2] = { {0,1},{0,2},{1,3},{2,3},{3,4},{4,5} };
	int e = (int)(sizeof(edges) / sizeof(edges[0]));
	for (int i = 0; i < e; i++) {
		int u = edges[i][0], w = edges[i][1];
		adj[u][w] = adj[w][u] = 1;          /* 무방향이므로 양쪽 다 1 */
	}

	int start = 0, goal = 5;
	int visited[V] = { 0 };
	int dist[V];
	for (int i = 0; i < V; i++) dist[i] = -1;   /* -1 = 아직 도달 못함 */

	/* ── 직접 구현: BFS (대기열은 라이브러리 linkedQueue) ──
	   시작역을 큐에 넣고, 큐에서 꺼낸 역의 이웃 중 미방문을 큐에 넣으며
	   거리(=구간 수)를 1씩 늘린다. 큐는 먼저 도달한 순서를 보장하므로
	   가장 먼저 goal에 도달했을 때의 거리가 최소 구간 수가 된다. */
	LQueue* q = createLQueue();
	enLQueue(q, start);
	visited[start] = 1;
	dist[start] = 0;
	while (!isLQEmpty(q)) {
		int cur = deLQueue(q);
		for (int nx = 0; nx < V; nx++) {
			if (adj[cur][nx] && !visited[nx]) {
				visited[nx] = 1;
				dist[nx] = dist[cur] + 1;   /* 한 구간 더 */
				enLQueue(q, nx);
			}
		}
	}
	freeLQueue(q);

	if (dist[goal] >= 0)
		printf("%d역 -> %d역 : 최소 %d개 구간\n", start, goal, dist[goal]);
	else
		printf("%d역 -> %d역 : 도달 불가\n", start, goal);
	return 0;
}
