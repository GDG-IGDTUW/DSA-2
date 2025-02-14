import java.util.*;

class BusRoutePlanner {
    private int n;
    private List<int[]>[] adj;

    public BusRoutePlanner(int n, int[][] routes) {
        this.n = n;
        this.adj = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            adj[i] = new ArrayList<>();
        }
        buildGraph(routes);
    }

    private void buildGraph(int[][] routes) {
        for (int[] route : routes) {
            int start = route[0], end = route[1], time = route[2], startHour = route[3], endHour = route[4], penalty = route[5];
            adj[start].add(new int[]{end, time, startHour, endHour, penalty});
            adj[end].add(new int[]{start, time, startHour, endHour, penalty}); // Bidirectional
        }
    }

    public int[] findShortestRoute(int start, int destination, int maxTransfers, int currentHour) {
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> {
            if (a[1] != b[1]) return Integer.compare(a[1], b[1]); // Sort by time
            if (a[3] != b[3]) return Integer.compare(a[3], b[3]); // Sort by fewer transfers
            return Integer.compare(a[2], b[2]); // Sort by penalty
        });

        Map<String, Integer> visited = new HashMap<>();
        pq.offer(new int[]{start, 0, 0, 0}); // {stop, time, penalty, transfers}

        while (!pq.isEmpty()) {
            int[] curr = pq.poll();
            int stop = curr[0], time = curr[1], penalty = curr[2], transfers = curr[3];

            if (stop == destination) {
                return new int[]{time, penalty};
            }

            String key = stop + "-" + transfers;
            if (visited.containsKey(key) && visited.get(key) <= time) {
                continue;
            }
            visited.put(key, time);

            if (transfers > maxTransfers) continue;

            for (int[] route : adj[stop]) {
                int nextStop = route[0], travelTime = route[1], startHour = route[2], endHour = route[3], routePenalty = route[4];

                if (startHour <= currentHour && currentHour <= endHour) {
                    pq.offer(new int[]{nextStop, time + travelTime, penalty + routePenalty, transfers + 1});
                }
            }
        }
        return new int[]{-1, -1}; // No valid route found
    }

    public static void main(String[] args) {
        int n = 5;
        int[][] routes = {
            {0, 1, 3, 6, 20, 2},
            {1, 2, 2, 8, 18, 3},
            {0, 2, 6, 10, 16, 1},
            {2, 3, 1, 9, 21, 4},
            {3, 4, 4, 6, 20, 0}
        };
        int start = 0, destination = 4, maxTransfers = 2, currentHour = 15;

        BusRoutePlanner planner = new BusRoutePlanner(n, routes);
        System.out.println(Arrays.toString(planner.findShortestRoute(start, destination, maxTransfers, currentHour)));
    }
}
