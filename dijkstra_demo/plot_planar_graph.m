function h_out = plot_planar_graph(G, h_in)
% 
% Plot a weighted planar graph G 
% 
% INPUTS
%   h_in : optional figure handle
%   
% OUTPUTS  
%   h_out : figure handle
%
% Author: f.maire@qut.edu.au 
% Created  2013-04-27

if nargin < 2
    h_out = figure;
else
    h_out = h_in;
end

figure(h_out)
triplot(G.tri, G.xy(:,1),  G.xy(:,2), 'green')

hold on

for i=1:size(G.xy,1)
    text(G.xy(i,1), G.xy(i,2), num2str(i), 'FontName', 'Bitstream Charter',...
        'Color', 'red','FontWeight','bold','FontSize',24);
    for j=i+1:size(G.xy,1)
        if G.adj(i,j)
            loc = (G.xy(i,:)+G.xy(j,:))/2;
            text(loc(1), loc(2), num2str(G.cost(i,j),'%5.2f'), 'FontName', 'Bitstream Charter',...
                'Color', 'blue','FontWeight','bold','FontSize',16);        
        end
    end % for j
end % for i

if isfield(G,'next')
   for k=1:size(G.adj,1)
       next_k = G.next(k);
       if next_k>0
           plot(G.xy([k next_k],1)', G.xy([k next_k],2)','-k')
       end
   end
end
hold off