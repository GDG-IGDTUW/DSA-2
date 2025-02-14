import java.util.*;

public class SonamKumari29_BusRoutePlanner {

    static class Route {
        int start, end, time, start_hour, end_hour, penalty;
        
        public Route(int start, int end, int time, int start_hour, int end_hour, int penalty) {
            this.start = start;
            this.end = end;
            this.time = time;
            this.start_hour = start_hour;
            this.end_hour = end_hour;
            this.penalty = penalty;
        }
    }

    public static class State {
        int stop, time, penalty, transfers;

        public State(int stop, int time, int penalty, int transfers) {
            this.stop = stop;
            this.time = time;
            this.penalty = penalty;
            this.transfers = transfers;
        }
    }

    public static int[] busRoutePlanner(int n, List<Route> routes, int start, int destination, int max_transfers, int current_hour) {
        // Graph initialization
        Map<Integer, List<Route>> graph = new HashMap<>();
        for (Route route : routes) {
            graph.computeIfAbsent(route.start, k -> new ArrayList<>()).add(route);
        }

        // Priority queue for Dijkstra's algorithm (min-heap)
        PriorityQueue<State> pq = new PriorityQueue<>(Comparator.comparingInt(state -> state.time));
        pq.add(new State(start, 0, 0, 0));  // Starting at 'start' with 0 time, 0 penalty, 0 transfers

        // Distance table: [stop][transfers] -> (time, penalty)
        int[][][] dist = new int[n][max_transfers + 1][2];  // {time, penalty}
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= max_transfers; j++) {
                dist[i][j] = new int[]{Integer.MAX_VALUE, Integer.MAX_VALUE};  // Set initial values as infinity
            }
        }
        dist[start][0] = new int[]{0, 0};  // Starting point

        while (!pq.isEmpty()) {
            State current = pq.poll();

            // If we reached the destination with valid transfer count, return the result
            if (current.stop == destination) {
                return new int[]{current.time, current.penalty};
            }

            // Explore all routes from the current bus stop
            if (current.transfers <= max_transfers) {
                List<Route> routesFromStop = graph.getOrDefault(current.stop, new ArrayList<>());
                for (Route route : routesFromStop) {
                    // Check if the route is valid based on current hour
                    if (current_hour >= route.start_hour && current_hour <= route.end_hour) {
                        int nextTransfers = current.transfers + 1;
                        if (nextTransfers <= max_transfers) {
                            int nextTime = current.time + route.time;
                            int nextPenalty = current.penalty + route.penalty;

                            // Relaxation: If we find a better time and penalty for the next stop with this number of transfers
                            if (nextTime < dist[route.end][nextTransfers][0] ||
                                (nextTime == dist[route.end][nextTransfers][0] && nextPenalty < dist[route.end][nextTransfers][1])) {
                                dist[route.end][nextTransfers] = new int[]{nextTime, nextPenalty};
                                pq.add(new State(route.end, nextTime, nextPenalty, nextTransfers));
                            }
                        }
                    }
                }
            }
        }

        // If no valid route was found
        return new int[]{-1};
    }

    public static void main(String[] args) {
        // Test Case
        List<Route> routes = new ArrayList<>();
        routes.add(new Route(0, 1, 3, 6, 20, 2));
        routes.add(new Route(1, 2, 2, 8, 18, 3));
        routes.add(new Route(0, 2, 6, 10, 16, 1));
        routes.add(new Route(2, 3, 1, 9, 21, 4));
        routes.add(new Route(3, 4, 4, 6, 20, 0));

        int[] result = busRoutePlanner(5, routes, 0, 4, 2, 15);
        if (result[0] == -1) {
            System.out.println("No valid route found.");
        } else {
            System.out.println("Shortest time: " + result[0] + " minutes, Total penalty: " + result[1]);
        }
    }
}
