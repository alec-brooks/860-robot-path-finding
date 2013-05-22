function G = make_planar_graph(n)
% 
% Build  a weighted planar graph G with n vertices
% 
% INPUTS
%   n : number of vertices
%   
% OUTPUTS  
%   G : the built graph
%      G.adj : n by n adjacency matrix
%      G.xy  : n by 2 matrix (vertex positions)
%      G.tri : Delaunay triangulation information
%      G.cost : n by n cost matrix (meaningful only for existing edges)
%
% Author: f.maire@qut.edu.au 
% Created  2013-04-27

% TODO: move the vertices for a more graceful graph 

G.adj = zeros(n); 
% G.xy = 10*rand(n,2);
G.xy = generatePoints(n, 2);
G.tri = delaunay(G.xy(:,1),G.xy(:,2));

for c=0:2
    vertexListA = G.tri(:,1+c);    
    vertexListB = G.tri(:,1+mod(c+1,3));    
    ind = sub2ind([n,n],vertexListA,vertexListB);
    G.adj(ind) = 1;
end

G.adj = (G.adj+G.adj') ~= 0;

costs = n*rand(n,n);

G.cost = costs+costs'; % make sure cost matrix is symmetric

    % generate points minDist  apart
    function XY = generatePoints(k, minDist)
        XY = zeros(k,2);
        XY(1,:) = 10*rand(1,2);
        for i=2:k
            farEnough = false;
            while ~farEnough
                P = 10*rand(1,2); % pick a point randomly
                D = XY(1:i-1,:)-repmat(P,i-1,1);       
                % test whether P is far from other points
                farEnough = min(sqrt(sum(D.*D,2))) > minDist;                 
            end
             XY(i,:) = P;
        end        
    end % generatePoints
        

end