function visited = reachable(G,v)
% Random exploration

    visited = [];
    toVisit = [v];

    while length(toVisit) >0

        fprintf('reachable:: toVisit = [ ')
        fprintf('%2d ',toVisit)
        fprintf(' ]\n')
        
        fprintf('reachable:: visited = [ ')
        fprintf('%2d ',visited)
        fprintf(' ]\n')


        % pick an element from 'toVisit' at random
        i = ceil( length(toVisit)*rand() );
        x = toVisit(i); 
        fprintf('reachable:: x = %2d\n\n',x)        
        toVisit(i) = []; % remove x from toVisit

        visited(end+1) = x;
        for y = G.Neighb{x}
            if not( ismember(y,toVisit) || ismember(y,visited) )
                toVisit(end+1) = y;
            end
        end
    end % while

end % reachable()


