function [D,next] = Dijkstra(G, s)
%
%  Implementation of Dijkstra algorithm
%   http://en.wikipedia.org/wiki/Dijkstra's_algorithm
%
% INPUTS
%   G : graph (made by make_planar_graph)
%   s : choose root node
%   
% OUTPUTS  
%   D     :  D(x) distance of a shortest path from x to s
%   next  :  next(x)  label of the neighbor of x closest to s
%
% Author: f.maire@qut.edu.au 
% Created  2013-04-28

n = size(G.adj,1); % number of vertices in the graph
D = Inf*ones(n,1); % D(x) : dist of the shortest path known so far from s to x
next = zeros(n,1); % next(x) : label of the neighbor of x to go to 

D(s) = 0; % Distance from s to s

Q = 1:n;   % list of vertices whose shortest distance is not yet known

while ~isempty(Q)
  
  [dx, ix] = min(D(Q));    
  x =  Q(ix); % provably closest vertex to s in Q
  Q(ix)=[]; % remove x from Q ;
  
  if dx == Inf
      break ;  % all remaining vertices are inaccessible from s
  end                                                 

  for y = intersect(find(G.adj(x,:)),Q)            
      altPathCost = dx + G.cost(x,y) ;
      if altPathCost < D(y)                                  % Relax (u,v,a)
          D(y) = altPathCost  ;
          next(y) = x ;
      end
  end % for
  
end % while
