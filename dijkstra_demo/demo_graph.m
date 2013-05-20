
%                      Dijsktra script

% Created by f.maire@qut.edu.au  on the 26th April 2013
% Revised on 27 April 2012





%---------------  G is structure representing a planar graph  -------------

G = make_planar_graph(8);

plot_planar_graph(G);

s = 3; % root vertex

[D,next] = Dijkstra(G, s);

G.next = next;

plot_planar_graph(G);


% ------------------------------------------------------------------------
% 
% h = waitbar(0,'Please wait...');
% for i=1:1000,
%     % computation here %
%     pause(0.01)
%     
%     waitbar(i/1000,h)
% end