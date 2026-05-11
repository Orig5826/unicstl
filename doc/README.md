
# unicstl

## 架构
```mermaid
flowchart TB
    subgraph bottom
        darray
        linklist
    end

    subgraph mid
        deque --> darray
    end

    subgraph top
        stack --> deque
        queue --> deque
    end
```
